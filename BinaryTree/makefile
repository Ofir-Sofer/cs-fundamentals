TARGET = test.out
CC = gcc
CFLAGS = -ansi -g -pedantic -I/home/ofir/Experis
OBJS = BinaryTree.o BinaryTree_main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

BinaryTree.o: BinaryTree.c BinaryTree.h BinaryTree_main.c
	$(CC) $(CFLAGS) -c BinaryTree.c

BinaryTree_main.o: BinaryTree_main.c BinaryTree.h
	$(CC) $(CFLAGS) -c BinaryTree_main.c
	
clean:
	rm -f $(TARGET) $(OBJS)
