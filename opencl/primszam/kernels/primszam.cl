__kernel void prime_test_kernel(__global const ulong *numbers,
                                __global uchar *results,
                                const uint count)
{
    uint gid = get_global_id(0);

    if (gid >= count) {
        return;
    }

    ulong x = numbers[gid];

    if (x < 2UL) {
        results[gid] = 0;
        return;
    }

    if (x == 2UL) {
        results[gid] = 1;
        return;
    }

    if ((x & 1UL) == 0UL) {
        results[gid] = 0;
        return;
    }

    for (ulong d = 3UL; d <= x / d; d += 2UL) {
        if (x % d == 0UL) {
            results[gid] = 0;
            return;
        }
    }

    results[gid] = 1;
}