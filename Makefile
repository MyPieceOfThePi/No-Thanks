CC = gcc
CFLAGS = -Iinclude
SRCS = $(wildcard src/*.c) $(wildcard src/Bots/*.c)
TARGET = bin/NoThanks

all:
	$(CC) $(CFLAGS) $(SRCS) -g -o $(TARGET)

clean:
	rm -f $(TARGET)