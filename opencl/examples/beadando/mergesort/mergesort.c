#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort(int arr[], int l, int r)
{
    if (l >= r) return;

    int m = l + (r - l) / 2;
    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, r);
    merge(arr, l, m, r);
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
    merge_sort(arr, 0, n - 1);
    clock_t end = clock();

    printf("Rendezett tomb:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nIdo: %.6f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}