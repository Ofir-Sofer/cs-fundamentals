#makefile Sort

TARGET = genericvector.out
CC = gcc
CFLAGS = -ansi -g -pedantic -Wall -Werror
OBJS = Vector.o Vector_main.o
VFLAGS = --log-file=memleak.log --leak-check=full --track-origins=yes -s

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

Vector.o: Vector.c Vector.h
	$(CC) $(CFLAGS) -c Vector.c
	
Vector_main.o: Vector_main.c Vector.h
	$(CC) $(CFLAGS) -c Vector_main.c

valgrind:
	valgrind $(VFLAGS) ./$(TARGET)
	
clean:
	rm -f $(TARGET) $(OBJS)
