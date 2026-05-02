#include "random_utils.h"

uint32_t make_sample_seed(int n, int sample_index)
{
    return 123456789u
           + (uint32_t)n * 1009u
           + (uint32_t)(sample_index + 1) * 9176u;
}

void fill_random_int_array(int* arr, int n, uint32_t seed, int max_value)
{
    uint32_t state = seed;

    for (int i = 0; i < n; i++) {
        state = state * 1664525u + 1013904223u;
        arr[i] = (int)(state % (uint32_t)max_value);
    }
}