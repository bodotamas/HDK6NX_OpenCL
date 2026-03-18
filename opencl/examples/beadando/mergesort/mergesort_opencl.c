#include "kernel_loader.h"

#define CL_TARGET_OPENCL_VERSION 120

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

static void print_build_log(cl_program program, cl_device_id device)
{
    size_t log_size = 0;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

    char* log = (char*)malloc(log_size + 1);
    if (!log) return;

    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
    log[log_size] = '\0';
    printf("%s\n", log);
    free(log);
}

static int is_sorted(const int* a, int n)
{
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) return 0;
    }
    return 1;
}

int main(void)
{
    const int n = 256;
    cl_int err;
    int file_err = 0;

    int* data = (int*)malloc(sizeof(int) * n);
    if (!data) {
        printf("Memóriafoglalási hiba.\n");
        return 1;
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 100;
    }

    cl_platform_id platform;
    cl_uint platform_count = 0;
    err = clGetPlatformIDs(1, &platform, &platform_count);
    if (err != CL_SUCCESS || platform_count == 0) {
        printf("clGetPlatformIDs hiba: %d\n", err);
        free(data);
        return 1;
    }

    cl_device_id device;
    cl_uint device_count = 0;

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &device_count);
    if (err != CL_SUCCESS || device_count == 0) {
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, &device_count);
        if (err != CL_SUCCESS || device_count == 0) {
            printf("Nem található használható OpenCL eszköz. Hibakód: %d\n", err);
            free(data);
            return 1;
        }
    }

    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateContext hiba: %d\n", err);
        free(data);
        return 1;
    }

    cl_command_queue queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateCommandQueue hiba: %d\n", err);
        clReleaseContext(context);
        free(data);
        return 1;
    }

    char* kernel_source = load_kernel_source("kernels/mergesort_kernel.cl", &file_err);
    if (file_err != 0 || !kernel_source) {
        printf("Nem sikerült betölteni a kernel forrást.\n");
        clReleaseCommandQueue(queue);
        clReleaseContext(context);
        free(data);
        return 1;
    }

    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_source, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateProgramWithSource hiba: %d\n", err);
        free(kernel_source);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);
        free(data);
        return 1;
    }

    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("clBuildProgram hiba: %d\n", err);
        print_build_log(program, device);
        clReleaseProgram(program);
        free(kernel_source);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);
        free(data);
        return 1;
    }

    cl_kernel kernel = clCreateKernel(program, "merge_pass", &err);
    if (err != CL_SUCCESS) {
        printf("clCreateKernel hiba: %d\n", err);
        clReleaseProgram(program);
        free(kernel_source);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);
        free(data);
        return 1;
    }

    size_t bytes = sizeof(int) * n;
    cl_mem buf_a = clCreateBuffer(context, CL_MEM_READ_WRITE, bytes, NULL, &err);
    cl_mem buf_b = clCreateBuffer(context, CL_MEM_READ_WRITE, bytes, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("clCreateBuffer hiba: %d\n", err);
        clReleaseKernel(kernel);
        clReleaseProgram(program);
        free(kernel_source);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);
        free(data);
        return 1;
    }

    err = clEnqueueWriteBuffer(queue, buf_a, CL_TRUE, 0, bytes, data, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("clEnqueueWriteBuffer hiba: %d\n", err);
        clReleaseMemObject(buf_a);
        clReleaseMemObject(buf_b);
        clReleaseKernel(kernel);
        clReleaseProgram(program);
        free(kernel_source);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);
        free(data);
        return 1;
    }

    cl_mem input = buf_a;
    cl_mem output = buf_b;
    cl_event last_event = NULL;

    for (int width = 1; width < n; width *= 2) {
        int pairs = (n + (2 * width) - 1) / (2 * width);
        size_t global_work_size = (size_t)pairs;

        err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
        err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);
        err |= clSetKernelArg(kernel, 2, sizeof(int), &width);
        err |= clSetKernelArg(kernel, 3, sizeof(int), &n);

        if (err != CL_SUCCESS) {
            printf("clSetKernelArg hiba: %d\n", err);
            if (last_event) clReleaseEvent(last_event);
            clReleaseMemObject(buf_a);
            clReleaseMemObject(buf_b);
            clReleaseKernel(kernel);
            clReleaseProgram(program);
            free(kernel_source);
            clReleaseCommandQueue(queue);
            clReleaseContext(context);
            free(data);
            return 1;
        }

        if (last_event) {
            clReleaseEvent(last_event);
            last_event = NULL;
        }

        err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &last_event);
        if (err != CL_SUCCESS) {
            printf("clEnqueueNDRangeKernel hiba: %d\n", err);
            clReleaseMemObject(buf_a);
            clReleaseMemObject(buf_b);
            clReleaseKernel(kernel);
            clReleaseProgram(program);
            free(kernel_source);
            clReleaseCommandQueue(queue);
            clReleaseContext(context);
            free(data);
            return 1;
        }

        cl_mem temp = input;
        input = output;
        output = temp;
    }

    clFinish(queue);

    err = clEnqueueReadBuffer(queue, input, CL_TRUE, 0, bytes, data, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("clEnqueueReadBuffer hiba: %d\n", err);
        if (last_event) clReleaseEvent(last_event);
        clReleaseMemObject(buf_a);
        clReleaseMemObject(buf_b);
        clReleaseKernel(kernel);
        clReleaseProgram(program);
        free(kernel_source);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);
        free(data);
        return 1;
    }

    printf("Rendezett tomb:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    printf("Ellenorzes: %s\n", is_sorted(data, n) ? "OK" : "HIBAS");

    if (last_event) {
        cl_ulong start_time = 0, end_time = 0;
        clGetEventProfilingInfo(last_event, CL_PROFILING_COMMAND_START, sizeof(start_time), &start_time, NULL);
        clGetEventProfilingInfo(last_event, CL_PROFILING_COMMAND_END, sizeof(end_time), &end_time, NULL);
        printf("Utolso kernel futasi ido: %.3f ms\n", (double)(end_time - start_time) / 1000000.0);
        clReleaseEvent(last_event);
    }

    clReleaseMemObject(buf_a);
    clReleaseMemObject(buf_b);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    free(kernel_source);
    free(data);

    return 0;
}