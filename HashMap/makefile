#makefile Hash Map

TARGET = HashMap.out
CC = gcc
LIST_PATH = ../genDoubleLinkedList
CFLAGS = -ansi -g -pedantic -Wall -Werror -I $(LIST_PATH)
#CFLAGS = -ansi -g -pedantic -Wall -I $(LIST_PATH)
OBJS = HashMap.o HashMap_main.o GenericDoubleLinkedList.o list_functions.o list_itr.o
VFLAGS = --log-file=memleak.log --leak-check=full --track-origins=yes -s

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

HashMap.o: HashMap.c HashMap.h
	$(CC) $(CFLAGS) -c HashMap.c

HashMap_main.o: HashMap_main.c HashMap.h
	$(CC) $(CFLAGS) -c HashMap_main.c
	
GenericDoubleLinkedList.o: $(LIST_PATH)/GenericDoubleLinkedList.c $(LIST_PATH)/GenericDoubleLinkedList.h
	$(CC) $(CFLAGS) -c $(LIST_PATH)/GenericDoubleLinkedList.c
	
list_functions.o: $(LIST_PATH)/list_functions.c $(LIST_PATH)/list_functions.h
	$(CC) $(CFLAGS) -c $(LIST_PATH)/list_functions.c
	
list_itr.o: $(LIST_PATH)/list_itr.c $(LIST_PATH)/list_itr.h
	$(CC) $(CFLAGS) -c $(LIST_PATH)/list_itr.c

valgrind:
	valgrind $(VFLAGS) ./$(TARGET)
	
clean:
	rm -f $(TARGET) $(OBJS)
