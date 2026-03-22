CC = gcc
CFLAGS = -Wall -Wextra -g -D_DEFAULT_SOURCE
TARGET = mysystem

SRCS = main.c serial.c protocol.c tcp_server.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c serial.h protocol.h tcp_server.h
	$(CC) $(CFLAGS) -c main.c

serial.o: serial.c serial.h
	$(CC) $(CFLAGS) -c serial.c

protocol.o: protocol.c protocol.h
	$(CC) $(CFLAGS) -c protocol.c

tcp_server.o: tcp_server.c tcp_server.h
	$(CC) $(CFLAGS) -c tcp_server.c

clean:
	rm -f $(OBJS) $(TARGET)