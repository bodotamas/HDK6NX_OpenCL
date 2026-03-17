#include "primszam.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KERNEL_FILE "kernels/primszam.cl"
#define KERNEL_NAME "prime_test_kernel"

static uint64_t rand_u64(void)
{
    uint64_t a = (uint64_t)(rand() & 0xFFFF);
    uint64_t b = (uint64_t)(rand() & 0xFFFF);
    uint64_t c = (uint64_t)(rand() & 0xFFFF);
    uint64_t d = (uint64_t)(rand() & 0xFFFF);

    return (a << 48) | (b << 32) | (c << 16) | d;
}

int generate_nbit_candidates(uint64_t *numbers, size_t count, unsigned bits)
{
    if (numbers == NULL) {
        return -1;
    }

    if (bits < 2 || bits > 63) {
        fprintf(stderr, "Hiba: a bitszam 2 es 63 koze essen.\n");
        return -1;
    }

    uint64_t low = 1ULL << (bits - 1);
    uint64_t mask = (1ULL << bits) - 1ULL;

    for (size_t i = 0; i < count; ++i) {
        uint64_t x = rand_u64();
        x &= mask;
        x |= low;
        x |= 1ULL;
        numbers[i] = x;
    }

    return 0;
}

static char *read_text_file(const char *filename, size_t *out_size)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Nem sikerult megnyitni: %s\n", filename);
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return NULL;
    }

    long size = ftell(fp);
    if (size < 0) {
        fclose(fp);
        return NULL;
    }

    rewind(fp);

    char *buffer = (char *)malloc((size_t)size + 1);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    size_t read_bytes = fread(buffer, 1, (size_t)size, fp);
    fclose(fp);

    if (read_bytes != (size_t)size) {
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0';

    if (out_size) {
        *out_size = (size_t)size;
    }

    return buffer;
}

static void print_build_log(cl_program program, cl_device_id device)
{
    size_t log_size = 0;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

    if (log_size == 0) {
        return;
    }

    char *log = (char *)malloc(log_size + 1);
    if (!log) {
        return;
    }

    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
    log[log_size] = '\0';

    fprintf(stderr, "\n===== OpenCL build log =====\n%s\n============================\n", log);
    free(log);
}

static int check_err(cl_int err, const char *msg)
{
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s (OpenCL hibakod: %d)\n", msg, err);
        return -1;
    }
    return 0;
}

int opencl_test_primes(const uint64_t *numbers, unsigned char *results, size_t count)
{
    if (numbers == NULL || results == NULL || count == 0) {
        return -1;
    }

    cl_int err;

    cl_platform_id platform = NULL;
    cl_device_id device = NULL;
    cl_context context = NULL;
    cl_command_queue queue = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_mem numbers_buffer = NULL;
    cl_mem results_buffer = NULL;

    char *source = NULL;
    size_t source_size = 0;

    err = clGetPlatformIDs(1, &platform, NULL);
    if (check_err(err, "clGetPlatformIDs hiba")) goto cleanup;

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
        if (check_err(err, "Nem talalhato OpenCL eszkoz")) goto cleanup;
    }

    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (check_err(err, "clCreateContext hiba")) goto cleanup;

    queue = clCreateCommandQueue(context, device, 0, &err);
    if (check_err(err, "clCreateCommandQueue hiba")) goto cleanup;

    source = read_text_file(KERNEL_FILE, &source_size);
    if (!source) {
        fprintf(stderr, "Nem sikerult beolvasni a kernel fajlt: %s\n", KERNEL_FILE);
        goto cleanup;
    }

    const char *sources[] = { source };
    program = clCreateProgramWithSource(context, 1, sources, &source_size, &err);
    if (check_err(err, "clCreateProgramWithSource hiba")) goto cleanup;

    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    print_build_log(program, device);
    if (check_err(err, "clBuildProgram hiba")) goto cleanup;

    kernel = clCreateKernel(program, KERNEL_NAME, &err);
    if (check_err(err, "clCreateKernel hiba")) {
        fprintf(stderr, "Keresett kernelnev: %s\n", KERNEL_NAME);
        goto cleanup;
    }

    numbers_buffer = clCreateBuffer(
        context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        count * sizeof(uint64_t),
        (void *)numbers,
        &err
    );
    if (check_err(err, "clCreateBuffer(numbers) hiba")) goto cleanup;

    results_buffer = clCreateBuffer(
        context,
        CL_MEM_WRITE_ONLY,
        count * sizeof(unsigned char),
        NULL,
        &err
    );
    if (check_err(err, "clCreateBuffer(results) hiba")) goto cleanup;

    cl_uint count_arg = (cl_uint)count;

    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &numbers_buffer);
    if (check_err(err, "clSetKernelArg(0) hiba")) goto cleanup;

    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &results_buffer);
    if (check_err(err, "clSetKernelArg(1) hiba")) goto cleanup;

    err = clSetKernelArg(kernel, 2, sizeof(cl_uint), &count_arg);
    if (check_err(err, "clSetKernelArg(2) hiba")) goto cleanup;

    size_t global_size = count;

    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, NULL, 0, NULL, NULL);
    if (check_err(err, "clEnqueueNDRangeKernel hiba")) goto cleanup;

    err = clFinish(queue);
    if (check_err(err, "clFinish hiba")) goto cleanup;

    err = clEnqueueReadBuffer(
        queue,
        results_buffer,
        CL_TRUE,
        0,
        count * sizeof(unsigned char),
        results,
        0,
        NULL,
        NULL
    );
    if (check_err(err, "clEnqueueReadBuffer hiba")) goto cleanup;

    free(source);
    clReleaseMemObject(results_buffer);
    clReleaseMemObject(numbers_buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    return 0;

cleanup:
    if (source) free(source);
    if (results_buffer) clReleaseMemObject(results_buffer);
    if (numbers_buffer) clReleaseMemObject(numbers_buffer);
    if (kernel) clReleaseKernel(kernel);
    if (program) clReleaseProgram(program);
    if (queue) clReleaseCommandQueue(queue);
    if (context) clReleaseContext(context);

    return -1;
}