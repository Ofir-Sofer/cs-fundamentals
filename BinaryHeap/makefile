#makefile Heap

VECTOR_PATH = ../vector
ADTDEFS_PATH = ../BinaryTree
TARGET = test.out
CC = gcc
CFLAGS = -ansi -g -pedantic -I $(VECTOR_PATH) -I $(ADTDEFS_PATH)
OBJS = BinaryHeap.o BinaryHeap_main.o Vector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

BinaryHeap.o: BinaryHeap.c BinaryHeap.h $(VECTOR_PATH)/Vector.h $(ADTDEFS_PATH)/ADTDefs.h
	$(CC) $(CFLAGS) -c BinaryHeap.c
	
Vector.o: $(VECTOR_PATH)/Vector.c $(VECTOR_PATH)/Vector.h $(ADTDEFS_PATH)/ADTDefs.h
	$(CC) $(CFLAGS) -c $(VECTOR_PATH)/Vector.c

BinaryHeap_main.o: BinaryHeap_main.c BinaryHeap.h $(VECTOR_PATH)/Vector.h $(ADTDEFS_PATH)/ADTDefs.h
	$(CC) $(CFLAGS) -c BinaryHeap_main.c

clean:
	rm -f $(TARGET) $(OBJS)
