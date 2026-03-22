CC = gcc
CFLAGS = -Wall -Wextra -g -D_DEFAULT_SOURCE
TARGET = mysystem

SRCS = main.c serial.c protocol.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c serial.h protocol.h
	$(CC) $(CFLAGS) -c main.c

serial.o: serial.c serial.h
	$(CC) $(CFLAGS) -c serial.c

protocol.o: protocol.c protocol.h
	$(CC) $(CFLAGS) -c protocol.c

clean:
	rm -f $(OBJS) $(TARGET)