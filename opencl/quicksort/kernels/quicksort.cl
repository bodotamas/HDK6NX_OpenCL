// Kernels/quicksort.cl

inline void swap_int(__global int* data, int a, int b)
{
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

kernel void quicksort_subrange(__global int* data, const int left, const int right)
{
    // Ezt a kernelt célszerű 1 work-itemmel indítani.
    if (get_global_id(0) != 0)
        return;

    if (left >= right)
        return;

    // Iteratív quicksort saját veremmel, hogy ne kelljen rekurzió.
    // Ha nagyobb intervallum kell, növeld a stack méretét.
    int lstack[1024];
    int rstack[1024];
    int top = -1;

    lstack[++top] = left;
    rstack[top] = right;

    while (top >= 0)
    {
        int l = lstack[top];
        int r = rstack[top--];

        while (l < r)
        {
            int i = l;
            int j = r;
            int pivot = data[l + (r - l) / 2];

            while (i <= j)
            {
                while (data[i] < pivot) i++;
                while (data[j] > pivot) j--;

                if (i <= j)
                {
                    swap_int(data, i, j);
                    i++;
                    j--;
                }
            }

            // A kisebb részt dolgozzuk fel azonnal,
            // a nagyobbat feltesszük a verembe.
            if ((j - l) < (r - i))
            {
                if (i < r)
                {
                    lstack[++top] = i;
                    rstack[top] = r;
                }
                r = j;
            }
            else
            {
                if (l < j)
                {
                    lstack[++top] = l;
                    rstack[top] = j;
                }
                l = i;
            }
        }
    }
}