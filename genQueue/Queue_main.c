#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

/*Test Fucnctions:*/
void TestCreateLegit();
void TestCreateZeroSize();
void TestCreateMinusSize();
void TestDestroyLegit();
void TestDoubleDestroy();
void TestInsertLegit();
void TestInsertNull();
void TestInsertOverflow();
void TestRemoveLegit();
void TestRemoveNULL();
void TestRemoveUnderflow();
void TestInsertModulus();
void TestQueueIsEmptyLegit();
void TestQueueIsEmptyNull();
void TestForEach();
void TestDestroyAllocated();

/*Assisting Functions:*/
int SumQueue(void* _element, void* _context);
void DestroyAllocatedInt(void* _element);

int main(void)
{
	TestCreateLegit();
	TestCreateZeroSize();
	TestCreateMinusSize();
	TestDestroyLegit();
	TestDoubleDestroy();
	TestInsertLegit();
	TestInsertNull();
	TestInsertOverflow();
	TestRemoveLegit();
	TestRemoveNULL();
	TestRemoveUnderflow();
	TestInsertModulus();
	TestQueueIsEmptyLegit();
	TestQueueIsEmptyNull();
	TestForEach();
	TestDestroyAllocated();
	return 0;
}

void TestCreateLegit()
{
	size_t initialSize = 5;
	Queue* queue = NULL;
	queue = QueueCreate(initialSize);
	if (queue != NULL)
	{
		printf("Test Create Legit PASSED\n");
		QueueDestroy(&queue, NULL);
	}
	else
	{
		printf("Test Create Legit **FAILED**\n");
	}	
}

void TestCreateZeroSize()
{
	size_t initialSize = 0;
	Queue* queue = NULL;
	queue = QueueCreate(initialSize);
	if(queue == NULL)
	{
		printf("Test Create Size Zero PASSED\n");
	}
	else
	{
		printf("Test Create Size Zero **FAILED**\n");
		QueueDestroy(&queue, NULL);
	}	
}

void TestCreateMinusSize()
{
	size_t initialSize = 0;
	Queue* queue = NULL;
	queue = QueueCreate(initialSize - 1);
	if (queue == NULL)
	{
		printf("Test Create Malloc Fail PASSED\n");
	}
	else
	{
		printf("Test Create Malloc Fail **FAILED**\n");
		QueueDestroy(&queue, NULL);
	}	
}

void TestDestroyLegit()
{
	size_t initialSize = 5;
	Queue* queue = NULL;
	queue = QueueCreate(initialSize);
	QueueDestroy(&queue, NULL);
	if (queue == NULL)
	{
		printf("Test Destroy Legit PASSED\n");
	}
	else
	{
		printf("Test Destroy Legit **FAILED**\n");
	}
}

void TestDoubleDestroy()
{
	size_t initialSize = 5;
	Queue* queue = NULL;
	queue = QueueCreate(initialSize);
	QueueDestroy(&queue, NULL);
	QueueDestroy(&queue, NULL);
	if (queue == NULL)
	{
		printf("Test Destroy Double PASSED\n");
	}
	else
	{
		printf("Test Destroy Double **FAILED**\n");
	}
}

void TestInsertLegit()
{
	size_t initialSize = 5;
	Queue* queue = NULL;
	QueueResult returned;
	int item = 4;
	queue = QueueCreate(initialSize);
	returned = QueueInsert(queue, &item);
	if(returned == QUEUE_SUCCESS && QueueIsEmpty(queue))
	{
		printf("Test Insert Legit PASSED\n");
	}
	else
	{
		printf("Test Insert Legit **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
}

void TestInsertNull()
{
	size_t initialSize = 5;
	Queue* queue = NULL;
	QueueResult returned1, returned2;
	int item = 4;
	queue = QueueCreate(initialSize);
	returned1 = QueueInsert(NULL, &item);
	returned2 = QueueInsert(queue, NULL);
	if(returned1 == QUEUE_UNINITIALIZED_ERROR && returned2 == QUEUE_DATA_UNINITIALIZED_ERROR)
	{
		printf("Test Insert NULL PASSED\n");
	}
	else
	{
		printf("Test Insert NULL **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
} 

void TestInsertOverflow()
{
	size_t initialSize = 3;
	Queue* queue = NULL;
	QueueResult returned;
	int items[] = {1, 2, 3, 4}, i;
	queue = QueueCreate(initialSize);
	for(i = 0 ; i <= initialSize ; ++i)
	{
		returned = QueueInsert(queue, &items[i]);	
	}
	if(returned == QUEUE_OVERFLOW_ERROR)
	{
		printf("Test Insert Overflow PASSED\n");
	}
	else
	{
		printf("Test Insert Overflow **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
}


void TestRemoveLegit()
{
	size_t initialSize = 5;
	Queue* queue = NULL;
	QueueResult returned;
	int item = 4;
	void *returnedItem;
	queue = QueueCreate(initialSize);
	QueueInsert(queue, &item);
	returned = QueueRemove(queue, &returnedItem);
	if(returned == QUEUE_SUCCESS && *(int*)returnedItem == item)
	{
		printf("Test Remove Legit PASSED\n");
	}
	else
	{
		printf("Test Remove Legit **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
}

void TestRemoveNULL()
{
	size_t initialSize = 5;
	Queue* queue = NULL;
	QueueResult returned1 ,returned2;
	int item = 4;
	void *returnedItem;
	queue = QueueCreate(initialSize);
	QueueInsert(queue, &item);
	returned1 = QueueRemove(NULL, &returnedItem);
	returned2 = QueueRemove(queue, NULL);
	if(returned1 == QUEUE_UNINITIALIZED_ERROR && returned2 == QUEUE_DATA_UNINITIALIZED_ERROR)
	{
		printf("Test Remove NULL PASSED\n");
	}
	else
	{
		printf("Test Remove NULL **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
}

void TestRemoveUnderflow()
{	
	size_t initialSize = 5;
	Queue* queue = NULL;
	QueueResult returned;
	void *returnedItem;
	queue = QueueCreate(initialSize);
	returned = QueueRemove(queue, &returnedItem);
	if(returned == QUEUE_DATA_NOT_FOUND_ERROR)
	{
		printf("Test Remove Underflow PASSED\n");
	}
	else
	{
		printf("Test Remove Underflow **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
}

void TestInsertModulus()
{
	size_t initialSize = 3;
	Queue* queue;
	int items[] = {1, 2, 3, 4, 5, 6}, i;
	void *returnedItem;
	queue = QueueCreate(initialSize);
	for(i = 0 ; i <= initialSize + 2 ; ++i)
	{
		QueueInsert(queue, &items[i]);
		QueueRemove(queue, &returnedItem);
		if(*(int*)returnedItem != items[i])
		{
			break;
		}
	}
	if(i == initialSize + 3)
	{
		printf("Test Insert Modulus PASSED\n");
	}
	else
	{
		printf("Test Insert Modulus **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
}

void TestQueueIsEmptyLegit()
{
	size_t initialSize = 3;
	Queue* queue;
	QueueResult returned1, returned2;
	int itemToInsert = 7;
	queue = QueueCreate(initialSize);
	returned1 = QueueIsEmpty(queue);
	QueueInsert(queue, &itemToInsert);
	returned2 = QueueIsEmpty(queue);
	if(!returned1 && returned2)
	{
		printf("Test Queue Is Empty PASSED\n");
	}
	else
	{
		printf("Test Queue Is Empty **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
}

void TestQueueIsEmptyNull()
{
	Queue* queue = NULL;
	if(QueueIsEmpty(queue) == 0)
	{
		printf("Test Queue Is Empty Null PASSED\n");
	}
	else
	{
		printf("Test Queue Is Empty Null **FAILED**\n");
	}
}

void TestForEach()
{
	size_t initialSize = 3;
	Queue* queue;
	int items[] = {1, 2, 3}, i, sumContext = 0, count;
	queue = QueueCreate(initialSize);
	for(i = 0 ; i < initialSize ; ++i)
	{
		QueueInsert(queue, &items[i]);
	}
	count = QueueForEach(queue, SumQueue, &sumContext);
	if(count == 3 && sumContext == 6)
	{
		printf("Test For Each PASSED\n");
	}
	else
	{
		printf("Test For Each **FAILED**\n");
	}
	QueueDestroy(&queue, NULL);
}

void TestDestroyAllocated()
{
	size_t initialSize = 5;
	int *allocatedItem = NULL;
	Queue* queue = NULL;
	queue = QueueCreate(initialSize);
	if((allocatedItem = (int*)calloc(initialSize, sizeof(int))) == NULL)
	{
		printf("Allocation Failed");
	}
	QueueInsert(queue, &allocatedItem);
	QueueDestroy(&queue, DestroyAllocatedInt);
	if (queue == NULL)
	{
		printf("Test Destroy Allocated PASSED\n");
	}
	else
	{
		printf("Test Destroy Allocated **FAILED**\n");
	}
}

/*Assisting Functions:*/
int SumQueue(void* _element, void* _context)
{
	*(int*)_context += *(int*)_element;
	return 1;
}

void DestroyAllocatedInt(void* _element)
{
	free(*(int**)_element);
}
