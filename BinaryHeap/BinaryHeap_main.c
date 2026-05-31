#include <stdio.h>
#include <stdlib.h>
#include "BinaryHeap.h"

/* Add tests with empty heap & Tests for OVERFLOW and UNDERFLOW*/
/*Test Functions:*/
static void TestCreateLegit();
static void TestCreateEmptyVector();
static void TestCreateVectorNull();
static void TestDestroyLegit();
static void TestDestroyDouble();
static void TestInsertLegit();
static void TestInsertLegitSmallValue();
static void TestInsertNull();
static void TestHeapMaxLegit();
static void TestExtractHeapMaxLegit();
static void TestHeapItemsNumLegit();
static void TestHeapPrint();
static void TestHeapPrintNull();

int main(void)
{
	TestCreateLegit();
	TestCreateEmptyVector();
	TestCreateVectorNull();
	TestDestroyLegit();
	TestDestroyDouble();
	TestInsertLegit();
	TestInsertLegitSmallValue();
	TestInsertNull();
	TestHeapMaxLegit();
	TestExtractHeapMaxLegit();
	TestHeapItemsNumLegit();
	TestHeapPrint();
	TestHeapPrintNull();
}

static void TestCreateLegit()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item;
	int arrToInsert[] = {5, 2, 1, 3, 18, 8, 7, 6, 12, 4}, arrAfterHeapify[] = {18, 12, 8, 6, 4, 1, 7, 5, 3, 2};
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		VectorAdd(vector, arrToInsert[i]);
	}
	heap = HeapBuild(vector);
	for(i = 0;i < 10;++i)
	{
		HeapGet(heap, i, &item);
		if(item != arrAfterHeapify[i])
		{
			break;
		}
	}
	if(GetHeapMagicNum(heap) == HeapGetMagicNum() && GetHeapSize(heap) == 10 && i == 10)
	{
		printf("Test Create Legit PASSED\n");
	}
	else
	{
		printf("Test Create Legit **FAILED**\n");
	}
	HeapDestroy(heap);
	VectorDestroy(vector);
}

static void TestCreateEmptyVector()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7;
	int i;
	vector = VectorCreate(initialSize, extensionBlockSize);
	heap = HeapBuild(vector);
	if(GetHeapMagicNum(heap) == HeapGetMagicNum() && GetHeapSize(heap) == 0)
	{
		printf("Test Create Empty Vector PASSED\n");
	}
	else
	{
		printf("Test Create Empty Vector **FAILED**\n");
	}
	HeapDestroy(heap);
	VectorDestroy(vector);
}

static void TestCreateVectorNull()
{
	Heap* heap = NULL;
	Vector *vector = NULL;
	heap = HeapBuild(vector);
	if(heap == NULL)
	{
		printf("Test Create Vector Null PASSED\n");
	}
	else
	{
		printf("Test Create Vector Null **FAILED**\n");
	}
}

static void TestDestroyLegit()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100;
		VectorAdd(vector, item);
	}
	heap = HeapBuild(vector);
	HeapDestroy(heap);
	if(GetHeapMagicNum(heap) != HeapGetMagicNum())
	{
		printf("Test Destroy Legit PASSED\n");
	}
	else
	{
		printf("Test Destroy Legit **FAILED**\n");
	}
	VectorDestroy(vector);
}

static void TestDestroyDouble()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100;
		VectorAdd(vector, item);
	}
	heap = HeapBuild(vector);
	HeapDestroy(heap);
	HeapDestroy(heap);
	if(GetHeapMagicNum(heap) != HeapGetMagicNum())
	{
		printf("Test Double Destroy PASSED\n");
	}
	else
	{
		printf("Test Double Destroy **FAILED**\n");
	}
	VectorDestroy(vector);
}

static void TestInsertLegit()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item, data = 101, extractData, returned;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100;
		VectorAdd(vector, item);
	}
	heap = HeapBuild(vector);
	HeapInsert(heap, data);
	returned = HeapGet(heap, i, &extractData);
	if(returned == ERR_OK && data != extractData && GetHeapSize(heap) == 11)
	{
		printf("Test Insert Legit PASSED\n");
	}
	else
	{
		printf("Test Insert Legit **FAILED**\n");
	}
	HeapDestroy(heap);
	VectorDestroy(vector);
}

static void TestInsertLegitSmallValue()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item, data = 10, extractData, returned;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100 + 11;
		VectorAdd(vector, item);
	}
	heap = HeapBuild(vector);
	HeapInsert(heap, data);
	returned = HeapGet(heap, i, &extractData);
	if(returned == ERR_OK && data == extractData && GetHeapSize(heap) == 11)
	{
		printf("Test Insert Small Value PASSED\n");
	}
	else
	{
		printf("Test Insert Small Value **FAILED**\n");
	}
	HeapDestroy(heap);
	VectorDestroy(vector);
}

static void TestInsertNull()
{
	Heap* heap = NULL;
	int data = 101;
	if(HeapInsert(heap, data) == ERR_NOT_INITIALIZED)
	{
		printf("Test Insert Null PASSED\n");
	}
	else
	{
		printf("Test Insert Null **FAILED**\n");
	}
}

static void TestHeapMaxLegit()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item, data = 101, extractData, returned;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100;
		VectorAdd(vector, item);
	}
	heap = HeapBuild(vector);
	HeapInsert(heap, data);
	returned = HeapMax(heap, &extractData);
	if(returned == ERR_OK && data == extractData)
	{
		printf("Test Heap Max PASSED\n");
	}
	else
	{
		printf("Test Heap Max **FAILED**\n");
	}
	HeapDestroy(heap);
	VectorDestroy(vector);
}

static void TestExtractHeapMaxLegit()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item, data = 101, extractData1, extractData2, returned, size1, size2;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100;
		VectorAdd(vector, item);
	}
	heap = HeapBuild(vector);
	HeapInsert(heap, data);
	size1 = GetHeapSize(heap);
	returned = HeapExtractMax(heap, &extractData1);
	HeapMax(heap, &extractData2);
	size2 = GetHeapSize(heap);
	if(returned == ERR_OK && data == extractData1 && data != extractData2 && size2 == size1 - 1)
	{
		printf("Test Extract Heap Max PASSED\n");
	}
	else
	{
		printf("Test Extract Heap Max **FAILED**\n");
	}
	HeapDestroy(heap);
	VectorDestroy(vector);
}

static void TestHeapItemsNumLegit()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, numOfItems;
	int i, item;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100;
		VectorAdd(vector, item);
	}
	heap = HeapBuild(vector);
	numOfItems = HeapItemsNum(heap);
	if(numOfItems == 10)
	{
		printf("Test Heap Items Num Legit PASSED\n");
	}
	else
	{
		printf("Test Heap Items Num Legit **FAILED**\n");
	}
	HeapDestroy(heap);
	VectorDestroy(vector);
}

static void TestHeapPrint()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item, data = 101, returned;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100;
		VectorAdd(vector, item);
	}
	heap = HeapBuild(vector);
	HeapPrint(heap);
	printf("Insert 101\n");
	HeapInsert(heap, data);
	HeapPrint(heap);
	HeapDestroy(heap);
	VectorDestroy(vector);
}

static void TestHeapPrintNull()
{
	Heap* heap = NULL;
	Vector *vector;
	size_t initialSize = 5, extensionBlockSize = 7, i;
	int item, data = 101, returned;
	vector = VectorCreate(initialSize, extensionBlockSize);
	for(i = 0;i < 10;++i)
	{
		item = rand()%100;
		VectorAdd(vector, item);
	}
	HeapPrint(heap);
	printf("Test Print Null Passed\n");
	VectorDestroy(vector);
}
