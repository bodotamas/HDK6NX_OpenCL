CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	OPENCL_FLAGS = -framework OpenCL
else
	OPENCL_FLAGS = -lOpenCL
endif

CPU_TARGET = quicksort_cpu
OPENCL_TARGET = quicksort_opencl

COMMON_SRC = src/random_utils.c
OPENCL_SRC = src/kernel_loader.c src/random_utils.c

all: $(CPU_TARGET) $(OPENCL_TARGET)

$(CPU_TARGET): quicksort.c $(COMMON_SRC) include/random_utils.h
	$(CC) $(CFLAGS) quicksort.c $(COMMON_SRC) -o $(CPU_TARGET)

$(OPENCL_TARGET): quicksort_opencl.c $(OPENCL_SRC) include/kernel_loader.h include/random_utils.h
	$(CC) $(CFLAGS) quicksort_opencl.c $(OPENCL_SRC) -o $(OPENCL_TARGET) $(OPENCL_FLAGS)

clean:
	rm -f $(CPU_TARGET) $(OPENCL_TARGET)

.PHONY: all clean