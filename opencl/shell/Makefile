CC = clang
CFLAGS = -std=c11 -Wall -Wextra -O2 -Iinclude
LDFLAGS = -framework OpenCL

TARGET = shellsort
SRC = src/main.c src/shellsort.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET) bench

clean:
	rm -f $(TARGET)