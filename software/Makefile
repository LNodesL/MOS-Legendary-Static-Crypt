CC = clang
CFLAGS = -Wall -Wextra -framework Cocoa
TARGET = hello_world
SOURCE = hello_world.m

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: all clean
