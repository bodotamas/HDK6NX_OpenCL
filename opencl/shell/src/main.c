// src/main.c
#include "shellsort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef enum
{
    INPUT_RANDOM = 0,
    INPUT_SORTED = 1,
    INPUT_REVERSE = 2
} InputType;

static const char* input_name(InputType t)
{
    switch (t)
    {
        case INPUT_RANDOM:  return "random";
        case INPUT_SORTED:  return "sorted";
        case INPUT_REVERSE: return "reverse";
        default:            return "unknown";
    }
}

static double now_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0;
}

static void fill_input(int* a, int n, InputType type)
{
    int i;

    switch (type)
    {
        case INPUT_RANDOM:
            for (i = 0; i < n; ++i)
                a[i] = rand() % 1000000;
            break;

        case INPUT_SORTED:
            for (i = 0; i < n; ++i)
                a[i] = i;
            break;

        case INPUT_REVERSE:
            for (i = 0; i < n; ++i)
                a[i] = n - i;
            break;
    }
}

static int is_sorted(const int* a, int n)
{
    int i;
    for (i = 1; i < n; ++i)
    {
        if (a[i - 1] > a[i])
            return 0;
    }
    return 1;
}

static void print_usage(const char* prog)
{
    printf("Használat:\n");
    printf("  %s run <n> <random|sorted|reverse> <shell|knuth|hibbard>\n", prog);
    printf("  %s bench\n", prog);
}

static GapSequenceType parse_gap(const char* s)
{
    if (strcmp(s, "shell") == 0)   return GAP_SHELL;
    if (strcmp(s, "knuth") == 0)   return GAP_KNUTH;
    if (strcmp(s, "hibbard") == 0) return GAP_HIBBARD;
    return GAP_SHELL;
}

static InputType parse_input(const char* s)
{
    if (strcmp(s, "random") == 0)  return INPUT_RANDOM;
    if (strcmp(s, "sorted") == 0)  return INPUT_SORTED;
    if (strcmp(s, "reverse") == 0) return INPUT_REVERSE;
    return INPUT_RANDOM;
}

static int run_single_test(ShellSortCL* clctx, int n, InputType input, GapSequenceType gap_type)
{
    int* data = (int*)malloc(sizeof(int) * (size_t)n);
    double t1, t2;

    if (!data)
    {
        fprintf(stderr, "Memóriafoglalási hiba.\n");
        return 1;
    }

    fill_input(data, n, input);

    t1 = now_ms();
    if (shellsort_opencl(clctx, data, n, gap_type) != 0)
    {
        fprintf(stderr, "Shell rendezés OpenCL-lel sikertelen.\n");
        free(data);
        return 1;
    }
    t2 = now_ms();

    printf("n=%d, input=%s, gaps=%s, ido=%.3f ms, sorted=%s\n",
           n,
           input_name(input),
           gap_sequence_name(gap_type),
           t2 - t1,
           is_sorted(data, n) ? "igen" : "nem");

    free(data);
    return 0;
}

static int benchmark(ShellSortCL* clctx)
{
    int sizes[] = {1000, 5000, 10000, 20000, 50000};
    InputType inputs[] = {INPUT_RANDOM, INPUT_SORTED, INPUT_REVERSE};
    GapSequenceType gaps[] = {GAP_SHELL, GAP_KNUTH, GAP_HIBBARD};

    int num_sizes = (int)(sizeof(sizes) / sizeof(sizes[0]));
    int num_inputs = (int)(sizeof(inputs) / sizeof(inputs[0]));
    int num_gaps = (int)(sizeof(gaps) / sizeof(gaps[0]));

    int i, j, k;

    printf("==== BENCHMARK ====\n");

    for (i = 0; i < num_sizes; ++i)
    {
        for (j = 0; j < num_inputs; ++j)
        {
            for (k = 0; k < num_gaps; ++k)
            {
                if (run_single_test(clctx, sizes[i], inputs[j], gaps[k]) != 0)
                    return 1;
            }
        }
        printf("\n");
    }

    return 0;
}

int main(int argc, char** argv)
{
    ShellSortCL clctx;
    const char* kernel_path = "Kernels/shellsort.cl";

    srand((unsigned int)time(NULL));

    if (shellsortcl_init(&clctx, kernel_path) != 0)
        return 1;

    if (argc < 2)
    {
        print_usage(argv[0]);
        shellsortcl_cleanup(&clctx);
        return 1;
    }

    if (strcmp(argv[1], "bench") == 0)
    {
        int rc = benchmark(&clctx);
        shellsortcl_cleanup(&clctx);
        return rc;
    }
    else if (strcmp(argv[1], "run") == 0)
    {
        int n;
        InputType input;
        GapSequenceType gap;

        if (argc != 5)
        {
            print_usage(argv[0]);
            shellsortcl_cleanup(&clctx);
            return 1;
        }

        n = atoi(argv[2]);
        input = parse_input(argv[3]);
        gap = parse_gap(argv[4]);

        {
            int rc = run_single_test(&clctx, n, input, gap);
            shellsortcl_cleanup(&clctx);
            return rc;
        }
    }
    else
    {
        print_usage(argv[0]);
        shellsortcl_cleanup(&clctx);
        return 1;
    }
}