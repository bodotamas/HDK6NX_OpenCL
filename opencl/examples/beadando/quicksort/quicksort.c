#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition_array(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int arr[], int low, int high)
{
    if (low >= high) return;

    int p = partition_array(arr, low, high);
    quick_sort(arr, low, p - 1);
    quick_sort(arr, p + 1, high);
}

int main(void)
{
    int n;
    printf("Elemek szama: ");
    scanf("%d", &n);

    int arr[n];
    srand((unsigned)time(NULL));

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    clock_t start = clock();
    quick_sort(arr, 0, n - 1);
    clock_t end = clock();

    printf("Rendezett tomb:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nIdo: %.6f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}