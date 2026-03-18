__kernel void merge_pass(__global const int* input,
                         __global int* output,
                         const int width,
                         const int n)
{
    int gid = get_global_id(0);
    int left = gid * 2 * width;

    if (left >= n) return;

    int mid = left + width;
    int right = left + 2 * width;

    if (mid > n) mid = n;
    if (right > n) right = n;

    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right) {
        if (input[i] <= input[j]) {
            output[k++] = input[i++];
        } else {
            output[k++] = input[j++];
        }
    }

    while (i < mid) {
        output[k++] = input[i++];
    }

    while (j < right) {
        output[k++] = input[j++];
    }
}