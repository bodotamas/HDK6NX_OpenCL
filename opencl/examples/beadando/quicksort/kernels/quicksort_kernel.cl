#define STACK_SIZE 256

__kernel void quicksort_kernel(__global int* data, const int n)
{
    if (get_global_id(0) != 0) return;
    if (n <= 1) return;

    int left_stack[STACK_SIZE];
    int right_stack[STACK_SIZE];
    int top = 0;

    left_stack[0] = 0;
    right_stack[0] = n - 1;

    while (top >= 0) {
        int left = left_stack[top];
        int right = right_stack[top];
        top--;

        while (left < right) {
            int i = left - 1;
            int j = right + 1;
            int pivot = data[left + (right - left) / 2];

            while (1) {
                do {
                    i++;
                } while (data[i] < pivot);

                do {
                    j--;
                } while (data[j] > pivot);

                if (i >= j) {
                    break;
                }

                {
                    int temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }

            if ((j - left) < (right - (j + 1))) {
                if (j + 1 < right) {
                    top++;
                    left_stack[top] = j + 1;
                    right_stack[top] = right;
                }
                right = j;
            } else {
                if (left < j) {
                    top++;
                    left_stack[top] = left;
                    right_stack[top] = j;
                }
                left = j + 1;
            }
        }
    }
}