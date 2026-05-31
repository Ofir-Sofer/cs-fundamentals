#ifndef __BINARYHEAP_H__
#define __BINARYHEAP_H__
#define MAGIC_NUM 159357
#include "ADTDefs.h"
#include "Vector.h"

/*insert explantion in vector errors*/
typedef struct Heap Heap;

/*description- This function builds a Heap struct
input- a struct of Vector
output- Heap pointer
	NULL
errors- NULL- if vector is NULL or allocation failed*/
Heap* HeapBuild(Vector* _vec); /* O(n) */

/*description- this function destroys a Heap struct
input- _heap- pointer to Heap struct
output- none
errors- none*/
void HeapDestroy(Heap* _heap);

/*description- this function inserts a new value to Heap
input- Heap pointer
	data to insert
output- ERR_OK
	ERR_NOT_INITIALIZED
	ERR_ALOCATION_FAILED
	ERR_OVERFLOW
errors- ERR_NOT_INITIALIZED - _heap is NULL ot vector error
	Vector Errors- ERR_ALOCATION_FAILED, ERR_OVERFLOW*/
ADTErr HeapInsert(Heap* _heap, int _data); /* O(log n) */

/*description- this function returns the highest value in Heap
input- Heap pointer
	pointer to data to insert the highest value
output- ERR_OK
	ERR_NOT_INITIALIZED
	ERR_OVERFLOW
	ERR_REALOOCATION_FAILED
errors- ERR_NOT_INITIALIZED Heap is NULL
	Vector Errors- ERR_REALOOCATION_FAILED, ERR_OVERFLOW*/
ADTErr HeapMax(Heap* _heap, int* _data);

/*description- This function extracts the maximum value in Heap while keeping the correct form
input- _heap- pointer to Heap
	pointer to store the extracted data
output- ERR_OK
	ERR_NOT_INITIALIZED
	ERR_WRONG_INDEX
	ERR_UNDERFLOW
errors- ERR_NOT_INITIALIZED heap or data == NULL, or vector errors
	Vector Errors- ERR_WRONG_INDEX, ERR_UNDERFLOW*/
ADTErr HeapExtractMax(Heap* _heap, int* _data); /* O(log n) */

/*description- This function retruns the number of elements in struct Heap
input- _heap- pointer to Heap
output- number of elements
	ERR_NOT_INITIALIZED
errors- 0 heap is NULL or empty*/
size_t HeapItemsNum(Heap* _heap);

/*description- This function prints the Heap
input- _heap- pointer to Heap
output- none
errors- none*/
void HeapPrint(Heap* _heap);

#endif/*__BINARYHEAP_H__*/
