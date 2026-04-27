#pragma once

#include <CL/cl.h>

#ifdef __cplusplus
extern "C" {
#endif

cl_kernel create_quicksort_kernel(cl_context context, cl_device_id device, cl_program* out_program);

cl_int run_quicksort_subrange(
    cl_command_queue queue,
    cl_kernel kernel,
    cl_mem data_buffer,
    int left,
    int right
);

#ifdef __cplusplus
}
#endif