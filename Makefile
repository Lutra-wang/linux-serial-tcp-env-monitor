CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = test

SRCS = main.c protocol.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c protocol.h
	$(CC) $(CFLAGS) -c main.c

protocol.o: protocol.c protocol.h
	$(CC) $(CFLAGS) -c protocol.c

clean:
	rm -f $(OBJS) $(TARGET)