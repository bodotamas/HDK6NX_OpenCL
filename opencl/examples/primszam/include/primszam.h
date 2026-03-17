#ifndef PRIMSZAM_H
#define PRIMSZAM_H

#include <stddef.h>
#include <stdint.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

int generate_nbit_candidates(uint64_t *numbers, size_t count, unsigned bits);
int opencl_test_primes(const uint64_t *numbers, unsigned char *results, size_t count);

#endif