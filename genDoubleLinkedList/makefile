# Generic Double Link List & itr

TARGET = genDLL.out
CC = gcc
CFLAGS = -ansi -g -pedantic -Wall -Werror
OBJS = GenericDoubleLinkedList.o GenericDoubleLinkedList_main.o list_itr.o list_functions.o
VFLAGS = --log-file=memleak.log --leak-check=full --track-origins=yes -s

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

GenericDoubleLinkedList.o: GenericDoubleLinkedList.c GenericDoubleLinkedList.h
	$(CC) $(CFLAGS) -c GenericDoubleLinkedList.c

GenericDoubleLinkedList_main.o: GenericDoubleLinkedList_main.c GenericDoubleLinkedList.h
	$(CC) $(CFLAGS) -c GenericDoubleLinkedList_main.c

list_itr.o: list_itr.c list_itr.h
	$(CC) $(CFLAGS) -c list_itr.c
	
list_functions.o: list_functions.c list_functions.h
	$(CC) $(CFLAGS) -c list_functions.c

valgrind:
	valgrind $(VFLAGS) ./$(TARGET)
	
clean:
	rm -f $(TARGET) $(OBJS)
