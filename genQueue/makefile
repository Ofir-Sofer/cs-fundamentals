#makefile Queue

TARGET = Queue.out
CC = gcc
CFLAGS = -ansi -g -pedantic -Wall -Werror
#CFLAGS = -ansi -g -pedantic -Wall
OBJS = Queue.o Queue_main.o
VFLAGS = --log-file=memleak.log --leak-check=full --track-origins=yes -s

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

Queue.o: Queue.c Queue.h
	$(CC) $(CFLAGS) -c Queue.c

Queue_main.o: Queue_main.c Queue.h
	$(CC) $(CFLAGS) -c Queue_main.c
	
valgrind:
	valgrind $(VFLAGS) ./$(TARGET)
	
clean:
	rm -f $(TARGET) $(OBJS)
