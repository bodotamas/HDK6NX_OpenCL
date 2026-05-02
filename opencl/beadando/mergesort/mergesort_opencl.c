#include "kernel_loader.h"
#include "random_utils.h"

#define CL_TARGET_OPENCL_VERSION 120

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#include <mach/mach_time.h>
#else
#include <CL/cl.h>
#include <time.h>
#endif

#define SAMPLE_COUNT 30
#define SIZE_COUNT 3
#define RANDOM_MAX_VALUE 100000

static const int test_sizes[SIZE_COUNT] = {1000, 2000, 3000};

static double now_ms(void)
{
#ifdef __APPLE__
    static mach_timebase_info_data_t timebase = {0, 0};
    uint64_t t;

    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }

    t = mach_absolute_time();
    return (double)t * (double)timebase.numer / (double)timebase.denom / 1000000.0;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
#endif
}

static void merge(int arr[], int temp[], int l, int m, int r)
{
    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= m) {
        temp[k++] = arr[i++];
    }

    while (j <= r) {
        temp[k++] = arr[j++];
    }

    for (i = l; i <= r; i++) {
        arr[i] = temp[i];
    }
}

static void merge_sort_recursive(int arr[], int temp[], int l, int r)
{
    if (l >= r) {
        return;
    }

    int m = l + (r - l) / 2;

    merge_sort_recursive(arr, temp, l, m);
    merge_sort_recursive(arr, temp, m + 1, r);
    merge(arr, temp, l, m, r);
}

static void merge_sort_cpu(int arr[], int temp[], int n)
{
    if (n <= 1) {
        return;
    }

    merge_sort_recursive(arr, temp, 0, n - 1);
}

static int is_sorted(const int* a, int n)
{
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            return 0;
        }
    }

    return 1;
}

static int arrays_equal(const int* a, const int* b, int n)
{
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

static void print_build_log(cl_program program, cl_device_id device)
{
    size_t log_size = 0;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

    char* log = (char*)malloc(log_size + 1);
    if (!log) {
        return;
    }

    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
    log[log_size] = '\0';

    printf("%s\n", log);
    free(log);
}

int main(void)
{
    const int max_n = 3000;
    const size_t max_bytes = sizeof(int) * (size_t)max_n;

    cl_int err;
    int file_err = 0;
    int exit_code = 0;

    int* base_data = NULL;
    int* cpu_data = NULL;
    int* cpu_temp = NULL;
    int* gpu_data = NULL;

    cl_platform_id platform = NULL;
    cl_device_id device = NULL;
    cl_context context = NULL;
    cl_command_queue queue = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_mem buf_a = NULL;
    cl_mem buf_b = NULL;
    char* kernel_source = NULL;

    base_data = (int*)malloc(max_bytes);
    cpu_data  = (int*)malloc(max_bytes);
    cpu_temp  = (int*)malloc(max_bytes);
    gpu_data  = (int*)malloc(max_bytes);

    if (!base_data || !cpu_data || !cpu_temp || !gpu_data) {
        printf("Memory allocation failed.\n");
        exit_code = 1;
        goto cleanup;
    }

    {
        cl_uint platform_count = 0;
        err = clGetPlatformIDs(1, &platform, &platform_count);

        if (err != CL_SUCCESS || platform_count == 0) {
            printf("clGetPlatformIDs failed. Error code: %d\n", err);
            exit_code = 1;
            goto cleanup;
        }
    }

    {
        cl_uint device_count = 0;
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &device_count);

        if (err != CL_SUCCESS || device_count == 0) {
            err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, &device_count);

            if (err != CL_SUCCESS || device_count == 0) {
                printf("No usable OpenCL device was found. Error code: %d\n", err);
                exit_code = 1;
                goto cleanup;
            }
        }
    }

    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateContext failed. Error code: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateCommandQueue failed. Error code: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    kernel_source = load_kernel_source("kernels/mergesort_kernel.cl", &file_err);
    if (file_err != 0 || !kernel_source) {
        printf("Failed to load the OpenCL kernel source file.\n");
        exit_code = 1;
        goto cleanup;
    }

    program = clCreateProgramWithSource(context, 1, (const char**)&kernel_source, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateProgramWithSource failed. Error code: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("clBuildProgram failed. Error code: %d\n", err);
        print_build_log(program, device);
        exit_code = 1;
        goto cleanup;
    }

    kernel = clCreateKernel(program, "merge_pass", &err);
    if (err != CL_SUCCESS) {
        printf("clCreateKernel failed. Error code: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    buf_a = clCreateBuffer(context, CL_MEM_READ_WRITE, max_bytes, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateBuffer for buf_a failed. Error code: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    buf_b = clCreateBuffer(context, CL_MEM_READ_WRITE, max_bytes, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateBuffer for buf_b failed. Error code: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    {
        char device_name[256] = {0};
        clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name), device_name, NULL);
        printf("Used OpenCL device: %s\n", device_name);
    }

    printf("OpenCL mergesort measurements\n");
    printf("Fixed input sizes: 1000, 2000, 3000\n");
    printf("Samples per input size: %d\n\n", SAMPLE_COUNT);

    printf("n;sample;opencl_total_time_ms;opencl_kernel_time_ms;validation\n");

    for (int s = 0; s < SIZE_COUNT; s++) {
        int n = test_sizes[s];
        size_t bytes = sizeof(int) * (size_t)n;

        double total_sum = 0.0;
        double total_min = 1e30;
        double total_max = 0.0;

        double kernel_sum = 0.0;
        double kernel_min = 1e30;
        double kernel_max = 0.0;

        for (int sample = 0; sample < SAMPLE_COUNT; sample++) {
            uint32_t seed = make_sample_seed(n, sample);
            fill_random_int_array(base_data, n, seed, RANDOM_MAX_VALUE);

            memcpy(cpu_data, base_data, bytes);
            merge_sort_cpu(cpu_data, cpu_temp, n);

            double total_start = now_ms();

            err = clEnqueueWriteBuffer(queue, buf_a, CL_TRUE, 0, bytes, base_data, 0, NULL, NULL);
            if (err != CL_SUCCESS) {
                printf("clEnqueueWriteBuffer failed. Error code: %d\n", err);
                exit_code = 1;
                goto cleanup;
            }

            cl_mem input = buf_a;
            cl_mem output = buf_b;
            double kernel_time_ms = 0.0;

            for (int width = 1; width < n; width *= 2) {
                int pairs = (n + (2 * width) - 1) / (2 * width);
                size_t global_work_size = (size_t)pairs;
                cl_event event = NULL;

                err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
                err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);
                err |= clSetKernelArg(kernel, 2, sizeof(int), &width);
                err |= clSetKernelArg(kernel, 3, sizeof(int), &n);

                if (err != CL_SUCCESS) {
                    printf("clSetKernelArg failed. Error code: %d\n", err);
                    exit_code = 1;
                    goto cleanup;
                }

                err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &event);
                if (err != CL_SUCCESS) {
                    printf("clEnqueueNDRangeKernel failed. Error code: %d\n", err);
                    exit_code = 1;
                    goto cleanup;
                }

                clWaitForEvents(1, &event);

                {
                    cl_ulong start_time = 0;
                    cl_ulong end_time = 0;

                    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
                                            sizeof(start_time), &start_time, NULL);
                    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
                                            sizeof(end_time), &end_time, NULL);

                    kernel_time_ms += (double)(end_time - start_time) / 1000000.0;
                }

                clReleaseEvent(event);

                {
                    cl_mem temp = input;
                    input = output;
                    output = temp;
                }
            }

            err = clEnqueueReadBuffer(queue, input, CL_TRUE, 0, bytes, gpu_data, 0, NULL, NULL);
            if (err != CL_SUCCESS) {
                printf("clEnqueueReadBuffer failed. Error code: %d\n", err);
                exit_code = 1;
                goto cleanup;
            }

            double total_end = now_ms();
            double total_elapsed = total_end - total_start;

            {
                int ok = is_sorted(gpu_data, n) && arrays_equal(cpu_data, gpu_data, n);

                printf("%d;%d;%.6f;%.6f;%s\n",
                       n,
                       sample + 1,
                       total_elapsed,
                       kernel_time_ms,
                       ok ? "OK" : "FAILED");

                if (!ok) {
                    printf("ERROR: OpenCL result does not match the CPU result. n=%d, sample=%d\n",
                           n, sample + 1);
                    exit_code = 1;
                    goto cleanup;
                }
            }

            total_sum += total_elapsed;
            if (total_elapsed < total_min) total_min = total_elapsed;
            if (total_elapsed > total_max) total_max = total_elapsed;

            kernel_sum += kernel_time_ms;
            if (kernel_time_ms < kernel_min) kernel_min = kernel_time_ms;
            if (kernel_time_ms > kernel_max) kernel_max = kernel_time_ms;
        }

        printf("\nSummary for %d elements:\n", n);
        printf("OpenCL total average: %.6f ms | min: %.6f ms | max: %.6f ms\n",
               total_sum / SAMPLE_COUNT, total_min, total_max);
        printf("OpenCL kernel average: %.6f ms | min: %.6f ms | max: %.6f ms\n\n",
               kernel_sum / SAMPLE_COUNT, kernel_min, kernel_max);
    }

cleanup:
    if (buf_a) clReleaseMemObject(buf_a);
    if (buf_b) clReleaseMemObject(buf_b);
    if (kernel) clReleaseKernel(kernel);
    if (program) clReleaseProgram(program);
    if (queue) clReleaseCommandQueue(queue);
    if (context) clReleaseContext(context);

    free(kernel_source);
    free(base_data);
    free(cpu_data);
    free(cpu_temp);
    free(gpu_data);

    return exit_code;
}