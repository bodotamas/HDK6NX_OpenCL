#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <stdint.h>

uint32_t make_sample_seed(int n, int sample_index);
void fill_random_int_array(int* arr, int n, uint32_t seed, int max_value);

#endif