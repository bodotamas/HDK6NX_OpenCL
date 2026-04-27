CC = cc
CFLAGS = -std=c11 -O2 -Wall -Wextra -Iinclude

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    OPENCL_LIBS = -framework OpenCL
else
    OPENCL_LIBS = -lOpenCL
endif

all: mergesort_cpu mergesortopencl

mergesort_cpu: mergesort.c
	$(CC) $(CFLAGS) -o mergesort_cpu mergesort.c

mergesortopencl: mergesort_opencl.c src/kernel_loader.c include/kernel_loader.h kernels/mergesort_kernel.cl
	$(CC) $(CFLAGS) -o mergesortopencl mergesort_opencl.c src/kernel_loader.c $(OPENCL_LIBS)

clean:
	rm -f mergesort_cpu mergesortopencl