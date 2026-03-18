CC = clang
CFLAGS = -std=c11 -O2 -Wall -Wextra -Iinclude
LDFLAGS = -framework OpenCL

all: quicksortopencl quicksort_cpu

quicksortopencl: quicksort_opencl.c src/kernel_loader.c
	$(CC) $(CFLAGS) quicksort_opencl.c src/kernel_loader.c -o quicksortopencl $(LDFLAGS)

quicksort_cpu: quicksort.c
	$(CC) $(CFLAGS) quicksort.c -o quicksort_cpu

clean:
	rm -f quicksortopencl quicksort_cpu