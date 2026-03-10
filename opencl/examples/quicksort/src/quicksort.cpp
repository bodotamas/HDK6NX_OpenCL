#include "quicksort.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

static std::string read_file(const char* path)
{
    std::ifstream file(path, std::ios::in);
    if (!file.is_open())
        return "";

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

cl_kernel create_quicksort_kernel(cl_context context, cl_device_id device, cl_program* out_program)
{
    const char* kernel_path = "kernels/quicksort.cl";
    std::string source = read_file(kernel_path);

    if (source.empty())
    {
        std::cerr << "Nem sikerült beolvasni: " << kernel_path << "\n";
        return nullptr;
    }

    const char* src_ptr = source.c_str();
    size_t src_size = source.size();

    cl_int err = CL_SUCCESS;
    cl_program program = clCreateProgramWithSource(context, 1, &src_ptr, &src_size, &err);
    if (err != CL_SUCCESS)
    {
        std::cerr << "clCreateProgramWithSource hiba: " << err << "\n";
        return nullptr;
    }

    err = clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
    if (err != CL_SUCCESS)
    {
        size_t log_size = 0;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &log_size);

        std::vector<char> log(log_size);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log.data(), nullptr);

        std::cerr << "OpenCL build hiba:\n" << log.data() << "\n";
        clReleaseProgram(program);
        return nullptr;
    }

    cl_kernel kernel = clCreateKernel(program, "quicksort_subrange", &err);
    if (err != CL_SUCCESS)
    {
        std::cerr << "clCreateKernel hiba: " << err << "\n";
        clReleaseProgram(program);
        return nullptr;
    }

    if (out_program)
        *out_program = program;
    else
        clReleaseProgram(program);

    return kernel;
}

cl_int run_quicksort_subrange(
    cl_command_queue queue,
    cl_kernel kernel,
    cl_mem data_buffer,
    int left,
    int right
)
{
    cl_int err = CL_SUCCESS;

    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &data_buffer);
    if (err != CL_SUCCESS) return err;

    err = clSetKernelArg(kernel, 1, sizeof(int), &left);
    if (err != CL_SUCCESS) return err;

    err = clSetKernelArg(kernel, 2, sizeof(int), &right);
    if (err != CL_SUCCESS) return err;

    size_t global_size = 1;
    size_t local_size = 1;

    err = clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &global_size, &local_size, 0, nullptr, nullptr);
    if (err != CL_SUCCESS) return err;

    return clFinish(queue);
}