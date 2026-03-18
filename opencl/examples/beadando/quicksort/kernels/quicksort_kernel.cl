__kernel void quicksort_kernel(__global int* arr, const int n)
{
    if (get_global_id(0) != 0) return;

    int stack_low[256];
    int stack_high[256];
    int top = -1;

    stack_low[++top] = 0;
    stack_high[top] = n - 1;

    while (top >= 0) {
        int low = stack_low[top];
        int high = stack_high[top--];

        while (low < high) {
            int pivot = arr[high];
            int i = low - 1;

            for (int j = low; j < high; j++) {
                if (arr[j] <= pivot) {
                    i++;
                    int tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }

            int p = i + 1;
            int tmp = arr[p];
            arr[p] = arr[high];
            arr[high] = tmp;

            if (p - 1 - low > high - (p + 1)) {
                if (low < p - 1) {
                    stack_low[++top] = low;
                    stack_high[top] = p - 1;
                }
                low = p + 1;
            } else {
                if (p + 1 < high) {
                    stack_low[++top] = p + 1;
                    stack_high[top] = high;
                }
                high = p - 1;
            }
        }
    }
}