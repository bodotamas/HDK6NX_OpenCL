#include "primszam.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BATCH_SIZE 256

static void print_usage(const char *progname)
{
    printf("Hasznalat: %s <bitszam> <db_primszam>\n", progname);
    printf("Pelda:     %s 20 5\n", progname);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        print_usage(argv[0]);
        return 1;
    }

    unsigned bits = (unsigned)strtoul(argv[1], NULL, 10);
    unsigned target_count = (unsigned)strtoul(argv[2], NULL, 10);

    if (bits < 2 || bits > 63) {
        fprintf(stderr, "Hiba: a bitszam 2 es 63 koze essen.\n");
        return 1;
    }

    if (target_count == 0) {
        fprintf(stderr, "Hiba: legalabb 1 primszamot kerj.\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    uint64_t *numbers = (uint64_t *)malloc(BATCH_SIZE * sizeof(uint64_t));
    unsigned char *results = (unsigned char *)malloc(BATCH_SIZE * sizeof(unsigned char));

    if (!numbers || !results) {
        fprintf(stderr, "Memoriafoglalasi hiba.\n");
        free(numbers);
        free(results);
        return 1;
    }

    printf("%u bites primszamok keresese OpenCL-lel...\n", bits);
    printf("Keresett darabszam: %u\n\n", target_count);

    unsigned found = 0;
    unsigned long long rounds = 0;

    while (found < target_count) {
        if (generate_nbit_candidates(numbers, BATCH_SIZE, bits) != 0) {
            fprintf(stderr, "Jeloltek generalasa sikertelen.\n");
            free(numbers);
            free(results);
            return 1;
        }

        if (opencl_test_primes(numbers, results, BATCH_SIZE) != 0) {
            fprintf(stderr, "OpenCL primalitasteszt sikertelen.\n");
            free(numbers);
            free(results);
            return 1;
        }

        ++rounds;

        for (size_t i = 0; i < BATCH_SIZE && found < target_count; ++i) {
            if (results[i]) {
                ++found;
                printf("%u. prim: %llu\n", found, (unsigned long long)numbers[i]);
            }
        }
    }

    printf("\nKesz. Korok szama: %llu\n", rounds);

    free(numbers);
    free(results);

    return 0;
}