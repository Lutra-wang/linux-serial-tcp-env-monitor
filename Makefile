CC = gcc
CFLAGS = -Wall -Wextra -g -D_DEFAULT_SOURCE
TARGET = serial_test

SRCS = main.c serial.c

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)