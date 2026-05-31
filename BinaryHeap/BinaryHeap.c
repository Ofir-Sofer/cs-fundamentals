#include <stdlib.h>/*for malloc*/
#include "BinaryHeap.h"
#define HEAP_MAGIC_NUM 135246
#define PARENT(i) (i-1)/2
#define LEFT(i) (2*(i)+1)
#define RIGHT(i) (2*(i) + 2)
#define IS_LEAF(index) (LEFT(index) >= _heapSize)
#define HEAPSWAP(a,b,t)\
	{\
	t temp1, temp2;\
	VectorGet(_heap->m_vec, a, &temp1);\
	VectorGet(_heap->m_vec, b, &temp2);\
	VectorSet(_heap->m_vec, a, temp2);\
	VectorSet(_heap->m_vec, b, temp1);\
	}
	
struct Heap
{
	Vector *m_vec;
	size_t m_heapSize;
	int m_magicNum;
};

/*Assiting Functions:*/
static void MaxHeapify(Heap *_heap);
static void Heapify(Heap *_heap, size_t _heapSize, size_t _index);
static void BubbleUp(Heap *_heap, size_t _index);
static size_t FindBiggest(Heap *_heap, size_t _index);

/*Get Functions:*/
int GetHeapMagicNum(Heap *_heap);
int GetMagicNum(Heap *_heap);

Heap* HeapBuild(Vector* _vec)
{
	Heap *newHeap;
	if(_vec == NULL)
	{
		return NULL;
	}
	newHeap = (Heap*)malloc(sizeof(Heap));
	if(newHeap == NULL)
	{
		return NULL;
	}
	newHeap->m_vec = _vec;
	newHeap->m_heapSize = GetVectorM_nItems(_vec);
	newHeap->m_magicNum = HEAP_MAGIC_NUM;
	if(newHeap->m_heapSize > 1)
	{
		MaxHeapify(newHeap);
	}
	return newHeap;
}


void HeapDestroy(Heap* _heap)
{
	if(_heap == NULL || _heap->m_magicNum != HEAP_MAGIC_NUM)
	{
		return;
	}
	_heap->m_magicNum = 0;
	free(_heap);
}

ADTErr HeapInsert(Heap* _heap, int _data)
{
	ADTErr returned;
	if(_heap == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	returned = VectorAdd(_heap->m_vec, _data);
/*	HeapPrint(_heap);*/
	if(returned != ERR_OK)
	{
		return returned;
	}
	_heap->m_heapSize = GetVectorM_nItems(_heap->m_vec);
	BubbleUp(_heap, _heap->m_heapSize - 1);
/*	HeapPrint(_heap);*/
	return returned;
}

ADTErr HeapMax(Heap* _heap, int* _data)
{
	if(_heap == NULL || _data == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorGet(_heap->m_vec, 0, _data);
}

ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
	int item;
	ADTErr returned;
	size_t numOfItems;
	if(_heap == NULL || _data == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	returned = VectorDelete(_heap->m_vec, &item);
	if(returned != ERR_OK)
	{
		return returned;
	}
	returned = VectorGet(_heap->m_vec, 0, _data);
	if(returned != ERR_OK)
	{
		return returned;
	}
	returned = VectorSet(_heap->m_vec, 0, item);
	if(returned != ERR_OK)
	{
		return returned;
	}
	returned = VectorItemsNum(_heap->m_vec, &numOfItems);
	Heapify(_heap, numOfItems, 0);
	if(returned != ERR_OK)
	{
		return returned;
	}
	_heap->m_heapSize = numOfItems;
	return returned;
}

size_t HeapItemsNum(Heap* _heap)
{
	if(_heap == NULL)
	{
		return 0;
	}
	return _heap->m_heapSize;
}

void HeapPrint(Heap* _heap)
{
	if(_heap == NULL)
	{
		return;
	}
	VectorPrint(_heap->m_vec);
}

/*Assiting Functions:*/

static void MaxHeapify(Heap *_heap)
{
	size_t i;
	for(i = PARENT(_heap->m_heapSize - 1);i >= 0 && i < _heap->m_heapSize - 1;--i)/*PARENT(_heap->m_heapSize) => Last Parent*/
	{
		Heapify(_heap, _heap->m_heapSize, i);
	}
}

static void Heapify(Heap *_heap, size_t _heapSize, size_t _index)
{
	size_t largest;
	if(IS_LEAF(_index) == TRUE)
	{
		return;
	}
	largest = FindBiggest(_heap, _index);
	if(largest != _index)
	{
		HEAPSWAP(_index, largest, int);
		Heapify(_heap, _heapSize, largest);
	}
}

static void BubbleUp(Heap *_heap, size_t _index)
{
	int newVal, parentVal;
	size_t parentIndex = PARENT(_index);
	if(parentIndex < 0)
	{
		return;
	}
	if(VectorGet(_heap->m_vec, _index, &newVal) == ERR_OK && VectorGet(_heap->m_vec, parentIndex, &parentVal) == ERR_OK \
		&& parentVal < newVal)
	{
		HEAPSWAP(_index, parentIndex, int);
		BubbleUp(_heap, parentIndex);
	}
}

static size_t FindBiggest(Heap *_heap, size_t _index)
{
	size_t left = LEFT(_index), right = RIGHT(_index), largest;
	int leftVal, rightVal, parentVal;
	VectorGet(_heap->m_vec, _index, &parentVal);
	if(left <= _heap->m_heapSize && VectorGet(_heap->m_vec, left, &leftVal) == ERR_OK && leftVal > parentVal)
	{
		largest = left;
		VectorGet(_heap->m_vec, largest, &parentVal);
	}
	else
	{
		largest = _index;
	}
	if(right <= _heap->m_heapSize && VectorGet(_heap->m_vec, right, &rightVal) == ERR_OK && rightVal > parentVal)
	{
		largest = right;
	}
	return largest;
}

/*Get Functions:*/

int GetHeapMagicNum(Heap *_heap)
{
	return _heap->m_magicNum;
}

int HeapGetMagicNum()
{
	return HEAP_MAGIC_NUM;
}

int GetHeapSize(Heap *_heap)
{
	return _heap->m_heapSize;
}

ADTErr HeapGet(Heap *_heap, size_t _index, int *_item)
{
	return VectorGet(_heap->m_vec, _index, _item);
}
