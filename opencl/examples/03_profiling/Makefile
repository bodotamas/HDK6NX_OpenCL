CC=clang
CFLAGS=-Wall -Wextra -O2 -Iinclude
LDFLAGS=-framework OpenCL

all: main

main: main.c src/kernel_loader.c
	$(CC) $(CFLAGS) main.c src/kernel_loader.c -o main $(LDFLAGS)

clean:
	rm -f main
