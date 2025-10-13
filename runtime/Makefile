CC = clang
CFLAGS = -Wall -Wextra -std=c99
TARGET = runtime
SOURCE = runtime.c
HEADER = software.h

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: all clean
