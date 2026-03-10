#ifndef SHELLSORT_H
#define SHELLSORT_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

typedef struct
{
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
} ShellSortCL;

typedef enum
{
    GAP_SHELL = 0,
    GAP_KNUTH = 1,
    GAP_HIBBARD = 2
} GapSequenceType;

int shellsortcl_init(ShellSortCL* clctx, const char* kernel_path);
void shellsortcl_cleanup(ShellSortCL* clctx);

int shellsort_opencl(ShellSortCL* clctx, int* data, int n, GapSequenceType gap_type);

const char* gap_sequence_name(GapSequenceType type);

#endif