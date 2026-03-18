CC = clang
CFLAGS = -std=c11 -O2 -Wall -Wextra -Iinclude
LDFLAGS = -framework OpenCL

all: mergesortopencl mergesort_cpu

mergesortopencl: mergesort_opencl.c src/kernel_loader.c
	$(CC) $(CFLAGS) mergesort_opencl.c src/kernel_loader.c -o mergesortopencl $(LDFLAGS)

mergesort_cpu: mergesort.c
	$(CC) $(CFLAGS) mergesort.c -o mergesort_cpu

clean:
	rm -f mergesortopencl mergesort_cpu