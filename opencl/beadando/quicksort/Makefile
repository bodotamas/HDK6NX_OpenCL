CC = cc
CFLAGS = -std=c11 -O2 -Wall -Wextra -Iinclude

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    OPENCL_LIBS = -framework OpenCL
else
    OPENCL_LIBS = -lOpenCL
endif

all: quicksort_cpu quicksortopencl

quicksort_cpu: quicksort.c
	$(CC) $(CFLAGS) -o quicksort_cpu quicksort.c

quicksortopencl: quicksort_opencl.c src/kernel_loader.c include/kernel_loader.h kernels/quicksort_kernel.cl
	$(CC) $(CFLAGS) -o quicksortopencl quicksort_opencl.c src/kernel_loader.c $(OPENCL_LIBS)

clean:
	rm -f quicksort_cpu quicksortopencl