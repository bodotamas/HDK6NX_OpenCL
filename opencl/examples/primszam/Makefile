CC = clang
CFLAGS = -std=c11 -O2 -Wall -Wextra -Iinclude -DCL_TARGET_OPENCL_VERSION=120 -Wno-deprecated-declarations
LDFLAGS = -framework OpenCL

TARGET = primszam

SRCS = main.c src/primszam.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.c include/primszam.h
	$(CC) $(CFLAGS) -c main.c -o main.o

src/primszam.o: src/primszam.c include/primszam.h
	$(CC) $(CFLAGS) -c src/primszam.c -o src/primszam.o

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET) 20 5