CC = gcc
CFLAGS = -Iinclude -g
SRCS = $(wildcard src/*.c) $(wildcard src/bots/*.c)
TARGET = bin/NoThanks

all:
	$(CC) $(CFLAGS) $(SRCS) -g -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET)