#include "kernel_loader.h"

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

static void fill_test_data(int* arr, int n, int sample_index)
{
    uint32_t state = 123456789u + (uint32_t)n * 1009u + (uint32_t)(sample_index + 1) * 9176u;

    for (int i = 0; i < n; i++) {
        state = state * 1664525u + 1013904223u;
        arr[i] = (int)(state % 100000u);
    }
}

static void swap_int(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int partition_hoare(int arr[], int low, int high)
{
    int pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap_int(&arr[i], &arr[j]);
    }
}

static void quicksort_recursive(int arr[], int low, int high)
{
    while (low < high) {
        int p = partition_hoare(arr, low, high);

        if (p - low < high - p) {
            quicksort_recursive(arr, low, p);
            low = p + 1;
        } else {
            quicksort_recursive(arr, p + 1, high);
            high = p;
        }
    }
}

static void quicksort_cpu(int arr[], int n)
{
    if (n <= 1) {
        return;
    }

    quicksort_recursive(arr, 0, n - 1);
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
    int* gpu_data = NULL;

    cl_platform_id platform = NULL;
    cl_device_id device = NULL;
    cl_context context = NULL;
    cl_command_queue queue = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_mem buf_data = NULL;
    char* kernel_source = NULL;

    base_data = (int*)malloc(max_bytes);
    cpu_data  = (int*)malloc(max_bytes);
    gpu_data  = (int*)malloc(max_bytes);

    if (!base_data || !cpu_data || !gpu_data) {
        printf("Memóriafoglalási hiba.\n");
        exit_code = 1;
        goto cleanup;
    }

    {
        cl_uint platform_count = 0;
        err = clGetPlatformIDs(1, &platform, &platform_count);
        if (err != CL_SUCCESS || platform_count == 0) {
            printf("clGetPlatformIDs hiba: %d\n", err);
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
                printf("Nem található használható OpenCL eszköz. Hibakód: %d\n", err);
                exit_code = 1;
                goto cleanup;
            }
        }
    }

    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateContext hiba: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateCommandQueue hiba: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    kernel_source = load_kernel_source("kernels/quicksort_kernel.cl", &file_err);
    if (file_err != 0 || !kernel_source) {
        printf("Nem sikerült betölteni a kernel forrást.\n");
        exit_code = 1;
        goto cleanup;
    }

    program = clCreateProgramWithSource(context, 1, (const char**)&kernel_source, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateProgramWithSource hiba: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("clBuildProgram hiba: %d\n", err);
        print_build_log(program, device);
        exit_code = 1;
        goto cleanup;
    }

    kernel = clCreateKernel(program, "quicksort_kernel", &err);
    if (err != CL_SUCCESS) {
        printf("clCreateKernel hiba: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    buf_data = clCreateBuffer(context, CL_MEM_READ_WRITE, max_bytes, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateBuffer hiba: %d\n", err);
        exit_code = 1;
        goto cleanup;
    }

    {
        char device_name[256] = {0};
        clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name), device_name, NULL);
        printf("Hasznalt OpenCL eszkoz: %s\n", device_name);
    }

    printf("OpenCL quicksort meresek\n");
    printf("Fix elemszamok: 1000, 2000, 3000\n");
    printf("Mintaszam meretenkent: %d\n\n", SAMPLE_COUNT);

    printf("n;minta;opencl_teljes_ido_ms;opencl_kernel_ido_ms;ellenorzes\n");

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
            fill_test_data(base_data, n, sample);

            memcpy(cpu_data, base_data, bytes);
            quicksort_cpu(cpu_data, n);

            double total_start = now_ms();

            err = clEnqueueWriteBuffer(queue, buf_data, CL_TRUE, 0, bytes, base_data, 0, NULL, NULL);
            if (err != CL_SUCCESS) {
                printf("clEnqueueWriteBuffer hiba: %d\n", err);
                exit_code = 1;
                goto cleanup;
            }

            err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &buf_data);
            err |= clSetKernelArg(kernel, 1, sizeof(int), &n);
            if (err != CL_SUCCESS) {
                printf("clSetKernelArg hiba: %d\n", err);
                exit_code = 1;
                goto cleanup;
            }

            {
                size_t global_work_size = 1;
                cl_event event = NULL;
                cl_ulong start_time = 0;
                cl_ulong end_time = 0;
                double kernel_time_ms = 0.0;

                err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &event);
                if (err != CL_SUCCESS) {
                    printf("clEnqueueNDRangeKernel hiba: %d\n", err);
                    exit_code = 1;
                    goto cleanup;
                }

                clWaitForEvents(1, &event);

                clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
                                        sizeof(start_time), &start_time, NULL);
                clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
                                        sizeof(end_time), &end_time, NULL);

                kernel_time_ms = (double)(end_time - start_time) / 1000000.0;

                clReleaseEvent(event);

                err = clEnqueueReadBuffer(queue, buf_data, CL_TRUE, 0, bytes, gpu_data, 0, NULL, NULL);
                if (err != CL_SUCCESS) {
                    printf("clEnqueueReadBuffer hiba: %d\n", err);
                    exit_code = 1;
                    goto cleanup;
                }

                {
                    double total_end = now_ms();
                    double total_elapsed = total_end - total_start;
                    int ok = is_sorted(gpu_data, n) && arrays_equal(cpu_data, gpu_data, n);

                    printf("%d;%d;%.6f;%.6f;%s\n",
                           n,
                           sample + 1,
                           total_elapsed,
                           kernel_time_ms,
                           ok ? "OK" : "HIBAS");

                    if (!ok) {
                        printf("HIBA: az OpenCL eredmény nem egyezik a CPU eredményével. n=%d, minta=%d\n",
                               n, sample + 1);
                        exit_code = 1;
                        goto cleanup;
                    }

                    total_sum += total_elapsed;
                    if (total_elapsed < total_min) total_min = total_elapsed;
                    if (total_elapsed > total_max) total_max = total_elapsed;

                    kernel_sum += kernel_time_ms;
                    if (kernel_time_ms < kernel_min) kernel_min = kernel_time_ms;
                    if (kernel_time_ms > kernel_max) kernel_max = kernel_time_ms;
                }
            }
        }

        printf("\n%d elem osszegzes:\n", n);
        printf("OpenCL teljes atlag: %.6f ms | min: %.6f ms | max: %.6f ms\n",
               total_sum / SAMPLE_COUNT, total_min, total_max);
        printf("OpenCL kernel atlag: %.6f ms | min: %.6f ms | max: %.6f ms\n\n",
               kernel_sum / SAMPLE_COUNT, kernel_min, kernel_max);
    }

cleanup:
    if (buf_data) clReleaseMemObject(buf_data);
    if (kernel) clReleaseKernel(kernel);
    if (program) clReleaseProgram(program);
    if (queue) clReleaseCommandQueue(queue);
    if (context) clReleaseContext(context);

    free(kernel_source);
    free(base_data);
    free(cpu_data);
    free(gpu_data);

    return exit_code;
}