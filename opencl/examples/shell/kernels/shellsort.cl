__kernel void shell_gap_pass(__global int* data, const int n, const int gap)
{
    int start = (int)get_global_id(0);

    if (start >= gap)
        return;

    // Gapped insertion sort az adott start osztályon:
    // start, start+gap, start+2*gap, ...
    for (int i = start + gap; i < n; i += gap)
    {
        int temp = data[i];
        int j = i;

        while (j >= gap && data[j - gap] > temp)
        {
            data[j] = data[j - gap];
            j -= gap;
        }

        data[j] = temp;
    }
}