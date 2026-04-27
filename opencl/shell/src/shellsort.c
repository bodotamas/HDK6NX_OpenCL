// src/shellsort.c
#include "shellsort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* read_text_file(const char* path, size_t* out_size)
{
    FILE* f = fopen(path, "rb");
    char* buffer;
    long size;

    if (!f)
        return NULL;

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    rewind(f);

    buffer = (char*)malloc((size_t)size + 1);
    if (!buffer)
    {
        fclose(f);
        return NULL;
    }

    if (fread(buffer, 1, (size_t)size, f) != (size_t)size)
    {
        fclose(f);
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0';
    fclose(f);

    if (out_size)
        *out_size = (size_t)size;

    return buffer;
}

static void print_build_log(cl_program program, cl_device_id device)
{
    size_t log_size = 0;
    char* log = NULL;

    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    log = (char*)malloc(log_size + 1);
    if (!log)
        return;

    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
    log[log_size] = '\0';

    fprintf(stderr, "OpenCL build log:\n%s\n", log);
    free(log);
}

static int choose_device(cl_platform_id* out_platform, cl_device_id* out_device)
{
    cl_uint num_platforms = 0;
    cl_platform_id* platforms = NULL;
    cl_int err;
    cl_uint i;

    err = clGetPlatformIDs(0, NULL, &num_platforms);
    if (err != CL_SUCCESS || num_platforms == 0)
    {
        fprintf(stderr, "Nem található OpenCL platform.\n");
        return -1;
    }

    platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
    if (!platforms)
        return -1;

    err = clGetPlatformIDs(num_platforms, platforms, NULL);
    if (err != CL_SUCCESS)
    {
        free(platforms);
        return -1;
    }

    // Először GPU
    for (i = 0; i < num_platforms; ++i)
    {
        err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 1, out_device, NULL);
        if (err == CL_SUCCESS)
        {
            *out_platform = platforms[i];
            free(platforms);
            return 0;
        }
    }

    // Ha nincs GPU, akkor CPU
    for (i = 0; i < num_platforms; ++i)
    {
        err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_CPU, 1, out_device, NULL);
        if (err == CL_SUCCESS)
        {
            *out_platform = platforms[i];
            free(platforms);
            return 0;
        }
    }

    free(platforms);
    fprintf(stderr, "Nem található használható OpenCL device.\n");
    return -1;
}

int shellsortcl_init(ShellSortCL* clctx, const char* kernel_path)
{
    cl_int err;
    char* source = NULL;
    size_t source_size = 0;

    if (!clctx)
        return -1;

    memset(clctx, 0, sizeof(*clctx));

    if (choose_device(&clctx->platform, &clctx->device) != 0)
        return -1;

    clctx->context = clCreateContext(NULL, 1, &clctx->device, NULL, NULL, &err);
    if (err != CL_SUCCESS || !clctx->context)
    {
        fprintf(stderr, "clCreateContext hiba: %d\n", err);
        return -1;
    }

#if defined(CL_VERSION_2_0)
    clctx->queue = clCreateCommandQueueWithProperties(clctx->context, clctx->device, 0, &err);
#else
    clctx->queue = clCreateCommandQueue(clctx->context, clctx->device, 0, &err);
#endif

    if (err != CL_SUCCESS || !clctx->queue)
    {
        fprintf(stderr, "clCreateCommandQueue hiba: %d\n", err);
        shellsortcl_cleanup(clctx);
        return -1;
    }

    source = read_text_file(kernel_path, &source_size);
    if (!source)
    {
        fprintf(stderr, "Nem sikerült beolvasni a kernel fájlt: %s\n", kernel_path);
        shellsortcl_cleanup(clctx);
        return -1;
    }

    {
        const char* src = source;
        clctx->program = clCreateProgramWithSource(clctx->context, 1, &src, &source_size, &err);
    }

    free(source);

    if (err != CL_SUCCESS || !clctx->program)
    {
        fprintf(stderr, "clCreateProgramWithSource hiba: %d\n", err);
        shellsortcl_cleanup(clctx);
        return -1;
    }

    err = clBuildProgram(clctx->program, 1, &clctx->device, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "clBuildProgram hiba: %d\n", err);
        print_build_log(clctx->program, clctx->device);
        shellsortcl_cleanup(clctx);
        return -1;
    }

    clctx->kernel = clCreateKernel(clctx->program, "shell_gap_pass", &err);
    if (err != CL_SUCCESS || !clctx->kernel)
    {
        fprintf(stderr, "clCreateKernel hiba: %d\n", err);
        shellsortcl_cleanup(clctx);
        return -1;
    }

    return 0;
}

void shellsortcl_cleanup(ShellSortCL* clctx)
{
    if (!clctx)
        return;

    if (clctx->kernel) clReleaseKernel(clctx->kernel);
    if (clctx->program) clReleaseProgram(clctx->program);
    if (clctx->queue) clReleaseCommandQueue(clctx->queue);
    if (clctx->context) clReleaseContext(clctx->context);

    memset(clctx, 0, sizeof(*clctx));
}

const char* gap_sequence_name(GapSequenceType type)
{
    switch (type)
    {
        case GAP_SHELL:   return "Shell";
        case GAP_KNUTH:   return "Knuth";
        case GAP_HIBBARD: return "Hibbard";
        default:          return "Unknown";
    }
}

static int build_shell_gaps(int n, int* gaps, int max_gaps)
{
    int count = 0;
    int gap = n / 2;

    while (gap > 0 && count < max_gaps)
    {
        gaps[count++] = gap;
        gap /= 2;
    }

    return count;
}

static int build_knuth_gaps(int n, int* gaps, int max_gaps)
{
    int temp[128];
    int count = 0;
    int h = 1;
    int i;

    while (h < n && count < 128)
    {
        temp[count++] = h;
        h = 3 * h + 1;
    }

    // fordított sorrend
    for (i = 0; i < count / 2; ++i)
    {
        int t = temp[i];
        temp[i] = temp[count - 1 - i];
        temp[count - 1 - i] = t;
    }

    if (count > max_gaps)
        count = max_gaps;

    for (i = 0; i < count; ++i)
        gaps[i] = temp[i];

    return count;
}

static int build_hibbard_gaps(int n, int* gaps, int max_gaps)
{
    int temp[128];
    int count = 0;
    int k = 1;
    int h;
    int i;

    while (count < 128)
    {
        h = (1 << k) - 1;
        if (h >= n)
            break;
        temp[count++] = h;
        ++k;
    }

    for (i = 0; i < count / 2; ++i)
    {
        int t = temp[i];
        temp[i] = temp[count - 1 - i];
        temp[count - 1 - i] = t;
    }

    if (count > max_gaps)
        count = max_gaps;

    for (i = 0; i < count; ++i)
        gaps[i] = temp[i];

    return count;
}

static int build_gap_sequence(int n, GapSequenceType type, int* gaps, int max_gaps)
{
    switch (type)
    {
        case GAP_SHELL:
            return build_shell_gaps(n, gaps, max_gaps);
        case GAP_KNUTH:
            return build_knuth_gaps(n, gaps, max_gaps);
        case GAP_HIBBARD:
            return build_hibbard_gaps(n, gaps, max_gaps);
        default:
            return 0;
    }
}

int shellsort_opencl(ShellSortCL* clctx, int* data, int n, GapSequenceType gap_type)
{
    cl_int err;
    cl_mem buffer = NULL;
    int gaps[128];
    int gap_count;
    int i;

    if (!clctx || !data || n <= 0)
        return -1;

    gap_count = build_gap_sequence(n, gap_type, gaps, 128);
    if (gap_count <= 0)
        return -1;

    buffer = clCreateBuffer(clctx->context,
                            CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                            sizeof(int) * (size_t)n,
                            data,
                            &err);
    if (err != CL_SUCCESS || !buffer)
    {
        fprintf(stderr, "clCreateBuffer hiba: %d\n", err);
        return -1;
    }

    for (i = 0; i < gap_count; ++i)
    {
        int gap = gaps[i];
        size_t global_size = (size_t)gap;

        err  = clSetKernelArg(clctx->kernel, 0, sizeof(cl_mem), &buffer);
        err |= clSetKernelArg(clctx->kernel, 1, sizeof(int), &n);
        err |= clSetKernelArg(clctx->kernel, 2, sizeof(int), &gap);

        if (err != CL_SUCCESS)
        {
            fprintf(stderr, "clSetKernelArg hiba: %d\n", err);
            clReleaseMemObject(buffer);
            return -1;
        }

        err = clEnqueueNDRangeKernel(clctx->queue,
                                     clctx->kernel,
                                     1,
                                     NULL,
                                     &global_size,
                                     NULL,
                                     0,
                                     NULL,
                                     NULL);
        if (err != CL_SUCCESS)
        {
            fprintf(stderr, "clEnqueueNDRangeKernel hiba: %d\n", err);
            clReleaseMemObject(buffer);
            return -1;
        }

        err = clFinish(clctx->queue);
        if (err != CL_SUCCESS)
        {
            fprintf(stderr, "clFinish hiba: %d\n", err);
            clReleaseMemObject(buffer);
            return -1;
        }
    }

    err = clEnqueueReadBuffer(clctx->queue,
                              buffer,
                              CL_TRUE,
                              0,
                              sizeof(int) * (size_t)n,
                              data,
                              0,
                              NULL,
                              NULL);

    clReleaseMemObject(buffer);

    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "clEnqueueReadBuffer hiba: %d\n", err);
        return -1;
    }

    return 0;
}