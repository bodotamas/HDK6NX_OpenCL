CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	OPENCL_FLAGS = -framework OpenCL
else
	OPENCL_FLAGS = -lOpenCL
endif

CPU_TARGET = mergesort_cpu
OPENCL_TARGET = mergesort_opencl

COMMON_SRC = src/random_utils.c
OPENCL_SRC = src/kernel_loader.c src/random_utils.c

all: $(CPU_TARGET) $(OPENCL_TARGET)

$(CPU_TARGET): mergesort.c $(COMMON_SRC) include/random_utils.h
	$(CC) $(CFLAGS) mergesort.c $(COMMON_SRC) -o $(CPU_TARGET)

$(OPENCL_TARGET): mergesort_opencl.c $(OPENCL_SRC) include/kernel_loader.h include/random_utils.h
	$(CC) $(CFLAGS) mergesort_opencl.c $(OPENCL_SRC) -o $(OPENCL_TARGET) $(OPENCL_FLAGS)

clean:
	rm -f $(CPU_TARGET) $(OPENCL_TARGET)

.PHONY: all clean