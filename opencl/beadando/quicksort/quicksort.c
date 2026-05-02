#include "random_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __APPLE__
#include <mach/mach_time.h>
#else
#include <time.h>
#endif

#define SAMPLE_COUNT 30
#define SIZE_COUNT 3
#define RANDOM_MAX_VALUE 100000

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

int main(void)
{
    printf("CPU quicksort measurements\n");
    printf("Fixed input sizes: 1000, 2000, 3000\n");
    printf("Samples per input size: %d\n\n", SAMPLE_COUNT);

    printf("n;sample;cpu_time_ms\n");

    for (int s = 0; s < SIZE_COUNT; s++) {
        int n = test_sizes[s];
        int* arr = (int*)malloc(sizeof(int) * (size_t)n);

        if (!arr) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        double sum = 0.0;
        double min = 1e30;
        double max = 0.0;

        for (int sample = 0; sample < SAMPLE_COUNT; sample++) {
            uint32_t seed = make_sample_seed(n, sample);
            fill_random_int_array(arr, n, seed, RANDOM_MAX_VALUE);

            double start = now_ms();
            quicksort_cpu(arr, n);
            double end = now_ms();

            double elapsed = end - start;

            if (!is_sorted(arr, n)) {
                printf("ERROR: CPU sorting failed. n=%d, sample=%d\n", n, sample + 1);
                free(arr);
                return 1;
            }

            printf("%d;%d;%.6f\n", n, sample + 1, elapsed);

            sum += elapsed;
            if (elapsed < min) min = elapsed;
            if (elapsed > max) max = elapsed;
        }

        printf("\nSummary for %d elements:\n", n);
        printf("Average: %.6f ms | min: %.6f ms | max: %.6f ms\n\n",
               sum / SAMPLE_COUNT, min, max);

        free(arr);
    }

    return 0;
}