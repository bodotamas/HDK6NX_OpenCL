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

static void fill_test_data(int* arr, int n, int sample_index)
{
    uint32_t state = 123456789u + (uint32_t)n * 1009u + (uint32_t)(sample_index + 1) * 9176u;

    for (int i = 0; i < n; i++) {
        state = state * 1664525u + 1013904223u;
        arr[i] = (int)(state % 100000u);
    }
}

static void merge(int arr[], int temp[], int l, int m, int r)
{
    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= m) {
        temp[k++] = arr[i++];
    }

    while (j <= r) {
        temp[k++] = arr[j++];
    }

    for (i = l; i <= r; i++) {
        arr[i] = temp[i];
    }
}

static void merge_sort_recursive(int arr[], int temp[], int l, int r)
{
    if (l >= r) {
        return;
    }

    int m = l + (r - l) / 2;

    merge_sort_recursive(arr, temp, l, m);
    merge_sort_recursive(arr, temp, m + 1, r);
    merge(arr, temp, l, m, r);
}

static void merge_sort_cpu(int arr[], int temp[], int n)
{
    if (n <= 1) {
        return;
    }

    merge_sort_recursive(arr, temp, 0, n - 1);
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
    printf("CPU mergesort meresek\n");
    printf("Fix elemszamok: 1000, 2000, 3000\n");
    printf("Mintaszam meretenkent: %d\n\n", SAMPLE_COUNT);

    printf("n;minta;cpu_ido_ms\n");

    for (int s = 0; s < SIZE_COUNT; s++) {
        int n = test_sizes[s];
        int* arr = (int*)malloc(sizeof(int) * n);
        int* temp = (int*)malloc(sizeof(int) * n);

        if (!arr || !temp) {
            printf("Memóriafoglalási hiba.\n");
            free(arr);
            free(temp);
            return 1;
        }

        double sum = 0.0;
        double min = 1e30;
        double max = 0.0;

        for (int sample = 0; sample < SAMPLE_COUNT; sample++) {
            fill_test_data(arr, n, sample);

            double start = now_ms();
            merge_sort_cpu(arr, temp, n);
            double end = now_ms();

            double elapsed = end - start;

            if (!is_sorted(arr, n)) {
                printf("HIBA: a CPU rendezés hibás. n=%d, minta=%d\n", n, sample + 1);
                free(arr);
                free(temp);
                return 1;
            }

            printf("%d;%d;%.6f\n", n, sample + 1, elapsed);

            sum += elapsed;
            if (elapsed < min) min = elapsed;
            if (elapsed > max) max = elapsed;
        }

        printf("\n%d elem osszegzes:\n", n);
        printf("Atlag: %.6f ms | min: %.6f ms | max: %.6f ms\n\n",
               sum / SAMPLE_COUNT, min, max);

        free(arr);
        free(temp);
    }

    return 0;
}