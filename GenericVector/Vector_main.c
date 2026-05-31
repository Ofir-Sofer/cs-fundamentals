#include <stdio.h>/*for size_t*/
#include <stdlib.h>/*for malloc*/
#include <string.h>/*for strcpy*/
#include "Vector.h"

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 , 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

typedef struct Person
{
	size_t m_id;
	char m_name[128];
} Person;

/*get functions:*/
size_t GetVectorOriginalSize(const Vector *_vector);
size_t GetVectorBlockSize(const Vector *_vector);

/*Assiting functions:*/
void DestroyIntElement(void* _item);
int	SumVecAction(void* _element, size_t _index, void* _context);
void DestroyPersonElement(void* _item);

/*Test Functions:*/
static void TestCreateZeros();
static void TestCreateNegativeInitialSize();
static void TestCreateZeroInitialSize();
static void TestCreateZeroBlockSize();
static void TestCreatePositiveInputCreate();
static void TestDestroyNULL();
static void TestDestroyLegit();
static void TestDoubleDestroy();
static void TestAddNULL();
static void TestAddLegit();
static void TestAddLegitWithRealloc();
static void TestAddReallocFailed();
static void TestAddLegitOverflow();
static void TestDeleteNULL();
static void TestDeleteLegit();
static void TestDeleteLegitWithRealloc();
static void TestDeleteLegitWithReallocOriginalSizeMaintain();
static void TestDeleteUnderflow();
static void TestGetVectorNULL();
static void TestGetItemNULL();
static void TestGetLegitIndex();
static void TestGetNotLegitIndex();
static void TestSetVectorNULL();
static void TestSetLegitIndex();
static void TestSetNotLegitIndex();
static void TestVectorSizeNULL();
static void TestVectorCapacityNULL();
static void TestForEach();
static void TestDestroyWithAllocatedElements();


int main(void)
{
	TestCreateZeros();
	TestCreateNegativeInitialSize();
	TestCreateZeroInitialSize();
	TestCreateZeroBlockSize();
	TestCreatePositiveInputCreate();
	TestDestroyNULL();
	TestDestroyLegit();
	TestDoubleDestroy();
	TestAddNULL();
	TestAddLegit();
	TestAddLegitWithRealloc();
	TestAddReallocFailed();
	TestAddLegitOverflow();
	TestDeleteNULL();
	TestDeleteLegit();
	TestDeleteLegitWithRealloc();
	TestDeleteLegitWithReallocOriginalSizeMaintain();
	TestDeleteUnderflow();
	TestGetVectorNULL();
	TestGetItemNULL();
	TestGetLegitIndex();
	TestGetNotLegitIndex();
	TestSetVectorNULL();
	TestSetLegitIndex();
	TestSetNotLegitIndex();
	TestVectorSizeNULL();
	TestVectorCapacityNULL();
	TestForEach();
	TestDestroyWithAllocatedElements();
	return 0;
}

static void TestCreateZeros()
{
	size_t initialSize = 0, extensionBlockSize = 0;
	Vector *vector;
	vector = VectorCreate(initialSize, extensionBlockSize);
	if (vector == NULL)
	{
		printf("Test Create Zeros PASSED\n");
	}
	else
	{
		printf("Test Create Zeros **FAILED**\n");
		VectorDestroy(&vector, DestroyIntElement);
	}
}

static void TestCreateNegativeInitialSize()
{
	size_t initialSize = -1, extensionBlockSize = 5;
	Vector *vector;
	vector = VectorCreate(initialSize, extensionBlockSize);
	if (vector == NULL)
	{
		printf("Test Create Negative Initial Size PASSED\n");
	}
	else
	{
		printf("Test Create Negative Initial Size **FAILED**\n");
		VectorDestroy(&vector, DestroyIntElement);
	}
}

static void TestCreateZeroInitialSize()
{
	size_t initialSize = 0, extensionBlockSize = 5;
	Vector *vector;
	vector = VectorCreate(initialSize, extensionBlockSize);
	if (vector != NULL)
	{
		printf("Test Create Zero Initial Size PASSED\n");
		VectorDestroy(&vector, DestroyIntElement);
	}
	else
	{
		printf("Test Create Zero Initial Size **FAILED**\n");
	}
}

static void TestCreateZeroBlockSize()
{
	size_t initialSize = 5, extensionBlockSize = 0;
	Vector *vector;
	vector = VectorCreate(initialSize, extensionBlockSize);
	if (vector != NULL)
	{
		printf("Test Create Zero Block Size PASSED\n");
		VectorDestroy(&vector, DestroyIntElement);
	}
	else
	{
		printf("Test Create Zero Block Size **FAILED**\n");
	}
}

static void TestCreatePositiveInputCreate()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector;
	int checkCapacity, checkM_nItems, checkOriginalSize, checkBlockSize;
	vector = VectorCreate(initialSize, extensionBlockSize);
	checkCapacity = (VectorCapacity(vector) == initialSize);
	checkM_nItems = (VectorSize(vector) == 0);
	checkOriginalSize = (GetVectorOriginalSize(vector) == initialSize);
	checkBlockSize = (GetVectorBlockSize(vector) == extensionBlockSize);
	if(checkCapacity && checkM_nItems && checkOriginalSize && checkBlockSize)
	{
		printf("Test Create Positive Input Create PASSED\n");
	}
	else
	{
		printf("Test Create Positive Input Create **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestDestroyNULL()
{
	Vector *vector = NULL;
	/*Test Destroy with NULL*/
	VectorDestroy(&vector, DestroyIntElement);
	if (vector == NULL)
	{
		printf("Test Destroy with NULL PASSED\n");
	}
	else
	{
		printf("Test Destroy with NULL **FAILED**\n");
	}
}

static void TestDestroyLegit()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	VectorDestroy(&vector, DestroyIntElement);
	if (vector == NULL)
	{
		printf("Test Destroy with Legit PASSED\n");
	}
	else
	{
		printf("Test Destroy with Legit **FAILED**\n");
	}
}

static void TestDoubleDestroy()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	VectorDestroy(&vector, DestroyIntElement);
	VectorDestroy(&vector, DestroyIntElement);
	if (vector == NULL)
	{
		printf("Test Destroy Double PASSED\n");
	}
	else
	{
		printf("Test Destroy Double **FAILED**\n");
	}
}

static void TestAddNULL()
{
	Vector *vector = NULL;
	int item = 0;
	if(VectorAppend(vector, &item) == VECTOR_UNINITIALIZED_ERROR)
	{
		printf("Test Add NULL PASSED\n");
	}
	else
	{
		printf("Test Add NULL **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestAddLegit()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int item = 465, checkItem;
	void *itemPtr;
	int checkCapacity, checkM_nItems, checkOriginalSize, checkBlockSize, returned;
	returned = (VectorAppend(vector, &item) == VECTOR_SUCCESS);
	checkCapacity = (VectorCapacity(vector) == initialSize);
	checkM_nItems = (VectorSize(vector) == 1);
	checkOriginalSize = (GetVectorOriginalSize(vector) == initialSize);
	checkBlockSize = (GetVectorBlockSize(vector) == extensionBlockSize);
	checkItem = (VectorGet(vector, 0, &itemPtr) == VECTOR_SUCCESS && *(int*)itemPtr == item);
	if(checkCapacity && checkM_nItems && checkOriginalSize && checkBlockSize && checkItem && returned)
	{
		printf("Test Add Legit PASSED\n");
	}
	else
	{
		printf("Test Add Legit **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestAddLegitWithRealloc()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int i = 0;
	void *itemPtr;
	int checkCapacity = 0, checkM_nItems = 0, checkOriginalSize = 0, checkBlockSize = 0, checkItem = 0, returned = 1;
	for (i = 0;i < initialSize + 1;++i)
	{
		returned *= (VectorAppend(vector, &arr[i]) == VECTOR_SUCCESS);	
	}
	i -= 1;
	checkCapacity = (VectorCapacity(vector) == initialSize + extensionBlockSize);
	checkM_nItems = (VectorSize(vector) == initialSize + 1);
	checkOriginalSize = (GetVectorOriginalSize(vector) == initialSize);
	checkBlockSize = (GetVectorBlockSize(vector) == extensionBlockSize);
	checkItem = (VectorGet(vector, i, &itemPtr) == VECTOR_SUCCESS && *(int*)itemPtr == arr[i]);
	if(checkCapacity && checkM_nItems && checkOriginalSize && checkBlockSize && checkItem && returned)
	{
		printf("Test Add Legit with Realloc PASSED\n");
	}
	else
	{
		printf("Test Add Legit with Realloc **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestAddReallocFailed()
{
	size_t initialSize = 5, extensionBlockSize = -6;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int i = 0;
	void *itemPtr;
	int checkCapacity = 0, checkM_nItems = 0, checkOriginalSize = 0, checkBlockSize = 0, checkItem = 0, returned = 1;
	for (i = 0;i < initialSize + 1;++i)
	{
		if(i == initialSize)
		{
			returned *= (VectorAppend(vector, &arr[i]) == VECTOR_REALLOCATION_ERROR);
			break;
		}
		VectorAppend(vector, &arr[i]);
	}
	i -= 1;
	checkCapacity = (VectorCapacity(vector) == initialSize);
	checkM_nItems = (VectorSize(vector) == initialSize);
	checkOriginalSize = (GetVectorOriginalSize(vector) == initialSize);
	checkBlockSize = (GetVectorBlockSize(vector) == extensionBlockSize);
	checkItem = (VectorGet(vector, i, &itemPtr) == VECTOR_SUCCESS && *(int*)itemPtr == arr[i]);
	if(checkCapacity && checkM_nItems && checkOriginalSize && checkBlockSize && checkItem && returned)
	{
		printf("Test Add Realloc Failed PASSED\n");
	}
	else
	{
		printf("Test Add Realloc Failed **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestAddLegitOverflow()
{
	size_t initialSize = 5, extensionBlockSize = 0;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int i = 0, mNItems = 0;
	void *itemPtr;
	int checkCapacity = 0, checkM_nItems = 0, checkOriginalSize = 0, checkBlockSize = 0, checkOverflow = 0, checkItem = 0;
	for (i = 0;i < initialSize;++i)
	{
		VectorAppend(vector, &arr[i]);	
	}
	checkOverflow = (VectorAppend(vector, &arr[i]) == VECTOR_OVERFLOW_ERROR);
	i -= 1;
	checkCapacity = (VectorCapacity(vector) == initialSize);
	mNItems = VectorSize(vector);
	checkM_nItems = (mNItems == initialSize);
	checkOriginalSize = (GetVectorOriginalSize(vector) == initialSize);
	checkBlockSize = (GetVectorBlockSize(vector) == extensionBlockSize);
	checkItem = (VectorGet(vector, mNItems - 1, &itemPtr) == VECTOR_SUCCESS && *(int*)itemPtr == arr[mNItems - 1]);
	if(checkCapacity && checkM_nItems && checkOriginalSize && checkBlockSize && checkItem && checkOverflow)
	{
		printf("Test Add Legit with Overflow PASSED\n");
	}
	else
	{
		printf("Test Add Legit with Overflow **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestDeleteNULL()
{
	Vector *vector = NULL;
	void *itemPtr;
	if(VectorRemove(vector, &itemPtr) == VECTOR_UNINITIALIZED_ERROR)
	{
		printf("Test Delete NULL PASSED\n");
	}
	else
	{
		printf("Test Delete NULL **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestDeleteLegit()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int checkItem, itemToAdd = 1245;
	void *itemPtr;
	int checkCapacity, checkM_nItems, checkOriginalSize, checkBlockSize, returned;
	VectorAppend(vector, &itemToAdd);
	returned = (VectorRemove(vector, &itemPtr) == VECTOR_SUCCESS);
	checkCapacity = (VectorCapacity(vector) == initialSize);
	checkM_nItems = (VectorSize(vector) == 0);
	checkOriginalSize = (GetVectorOriginalSize(vector) == initialSize);
	checkBlockSize = (GetVectorBlockSize(vector) == extensionBlockSize);
	checkItem = (*(int*)itemPtr == itemToAdd);
	if(checkCapacity && checkM_nItems && checkOriginalSize && checkBlockSize && checkItem && returned)
	{
		printf("Test Delete Legit PASSED\n");
	}
	else
	{
		printf("Test Delete Legit **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestDeleteLegitWithRealloc()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int checkItem = 0, i = 0, mNItems = 0;
	void *itemPtr;
	int checkCapacity = 0, checkM_nItems = 0, checkOriginalSize = 0, checkBlockSize = 0, returned = 1;
	for (i = 0;i < initialSize + 2 * extensionBlockSize + 1;++i)/*add items to increase array size and reallocate*/
	{
		VectorAppend(vector, &arr[i]);	
	}
	for (i = 1;i <= 2 * extensionBlockSize + 1;++i)/*delete items to decrease array size and reallocate*/
	{
		if (i == 2 * extensionBlockSize + 1)
		{
			/*make sure that after reallocation we still get the last value*/
			checkItem = (VectorGet(vector, initialSize, &itemPtr) == VECTOR_SUCCESS && *(int*)itemPtr == arr[initialSize]);
		}	
		returned *= (VectorRemove(vector, &itemPtr) == VECTOR_SUCCESS);
	}
	checkCapacity = (VectorCapacity(vector) == initialSize + extensionBlockSize);
	mNItems = VectorSize(vector);
	checkM_nItems = (mNItems == initialSize);
	checkOriginalSize = (GetVectorOriginalSize(vector) == initialSize);
	checkBlockSize = (GetVectorBlockSize(vector) == extensionBlockSize);
	if(checkCapacity && checkM_nItems && checkOriginalSize && checkBlockSize && checkItem && returned)
	{
		printf("Test Delete Legit with Realloc PASSED\n");
	}
	else
	{
		printf("Test Delete Legit with Realloc **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestDeleteLegitWithReallocOriginalSizeMaintain()
{
	size_t initialSize = 10, extensionBlockSize = 2;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int i = 0;
	void *itemPtr;
	int checkCapacity = 0, checkM_nItems = 0, checkOriginalSize = 0, checkBlockSize = 0, returned = 1;
	for (i = 0;i < initialSize + extensionBlockSize + 1;++i)/*add items to increase array size and reallocate*/
	{
		VectorAppend(vector, &arr[i]);	
	}
	for (i = VectorSize(vector);i > 0;--i)/*delete all items and make sure size = initial size*/
	{	
		returned *= (VectorRemove(vector, &itemPtr) == VECTOR_SUCCESS);
	}
	checkCapacity = (VectorCapacity(vector) == initialSize);
	checkM_nItems = (VectorSize(vector) == 0);
	checkOriginalSize = (GetVectorOriginalSize(vector) == initialSize);
	checkBlockSize = (GetVectorBlockSize(vector) == extensionBlockSize);
	if(checkCapacity && checkM_nItems && checkOriginalSize && checkBlockSize && returned)
	{
		printf("Test Delete Legit with Realloc and maintain Original Size PASSED\n");
	}
	else
	{
		printf("Test Delete Legit with Realloc and maintain Original Size **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestDeleteUnderflow()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	void *itemPtr;
	if(VectorRemove(vector, &itemPtr) == VECTOR_UNDERFLOW_ERROR)
	{
		printf("Test Delete Underflow PASSED\n");
	}
	else
	{
		printf("Test Delete Underflow **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestGetVectorNULL()
{
	Vector *vector = NULL;
	int index = 0;
	void *itemPtr;
	if(VectorGet(vector, index, &itemPtr) == VECTOR_UNINITIALIZED_ERROR)
	{
		printf("Test Get Vector NULL PASSED\n");
	}
	else
	{
		printf("Test Get Vector NULL **FAILED**\n");
	}
}

static void TestGetItemNULL()
{
	size_t initialSize = 10, extensionBlockSize = 2;
	Vector *vector = NULL;
	int index = 0;
	vector = VectorCreate(initialSize, extensionBlockSize);
	VectorAppend(vector, &arr[index]);
	if(VectorGet(vector, index, NULL) == VECTOR_UNINITIALIZED_ERROR)
	{
		printf("Test Get item NULL PASSED\n");
	}
	else
	{
		printf("Test Get item NULL **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestGetLegitIndex()
{
	size_t initialSize = 10, extensionBlockSize = 2;
	Vector *vector = NULL;
	int index = 0, itemToAdd = 1234;
	void *itemPtr;
	vector = VectorCreate(initialSize, extensionBlockSize);
	VectorAppend(vector, &itemToAdd);
	if(VectorGet(vector, index, &itemPtr) == VECTOR_SUCCESS && *(int*)itemPtr == itemToAdd)
	{
		printf("Test Get Legit PASSED\n");
	}
	else
	{
		printf("Test Get Legit **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestGetNotLegitIndex()
{
	size_t initialSize = 10, extensionBlockSize = 2;
	Vector *vector = NULL;
	size_t index = 2;
	int itemToAdd1 = 1234, itemToAdd2 = 4732;
	void *itemPtr;
	vector = VectorCreate(initialSize, extensionBlockSize);
	VectorAppend(vector, &itemToAdd1);
	VectorAppend(vector, &itemToAdd2);
	if(VectorGet(vector, index, &itemPtr) == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	{
		printf("Test Get Not Legit index PASSED\n");
	}
	else
	{
		printf("Test Get Not Legit index **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestSetVectorNULL()
{
	Vector *vector = NULL;
	size_t index = 0;
	int item = 5;
	if(VectorSet(vector, index, &item) == VECTOR_UNINITIALIZED_ERROR)
	{
		printf("Test Set Vector NULL PASSED\n");
	}
	else
	{
		printf("Test Set Vector NULL **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestSetLegitIndex()
{
	size_t initialSize = 10, extensionBlockSize = 2;
	Vector *vector;
	size_t index = 0;
	int itemToSet = 12567, itemToAdd = 1234, returned;
	void *itemPtr;
	vector = VectorCreate(initialSize, extensionBlockSize);
	VectorAppend(vector, &itemToAdd);
	returned = (VectorSet(vector, index, &itemToSet) == VECTOR_SUCCESS);
	VectorGet(vector, index, &itemPtr);
	if (returned && *(int*)itemPtr == itemToSet)
	{
		printf("Test Set Legit PASSED\n");
	}
	else
	{
		printf("Test Set Legit **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestSetNotLegitIndex()
{
	size_t initialSize = 10, extensionBlockSize = 2;
	Vector *vector;
	size_t index = 3;
	int itemToSet = 12567, itemToAdd = 1234, returned;
	vector = VectorCreate(initialSize, extensionBlockSize);
	VectorAppend(vector, &itemToAdd);
	returned = (VectorSet(vector, index, &itemToSet) == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR);
	if (returned)
	{
		printf("Test Set Not Legit index PASSED\n");
	}
	else
	{
		printf("Test Set Not Legit index **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestVectorSizeNULL()
{
	Vector *vector = NULL;
	if(VectorSize(vector) == 0)
	{
		printf("Test Vector Size NULL PASSED\n");
	}
	else
	{
		printf("Test Vector Size NULL **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestVectorCapacityNULL()
{
	Vector *vector = NULL;
	if(VectorCapacity(vector) == 0)
	{
		printf("Test Vector Capacity NULL PASSED\n");
	}
	else
	{
		printf("Test Vector Capacity NULL **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestForEach()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int i = 0, context = 0, sum = 0;
	for (i = 0;i < initialSize;++i)
	{
		VectorAppend(vector, &arr[i]);
		sum += arr[i];
	}
	VectorForEach(vector, SumVecAction, &context);
	if(sum == context)
	{
		printf("Test For Each PASSED\n");
	}
	else
	{
		printf("Test For Each **FAILED**\n");
	}
	VectorDestroy(&vector, DestroyIntElement);
}

static void TestDestroyWithAllocatedElements()
{
	size_t initialSize = 5, extensionBlockSize = 7;
	Vector *vector = VectorCreate(initialSize, extensionBlockSize);
	int i = 0;
	Person *person = NULL;
	char names[5][128] = {"Ofir", "Shir", "Balu", "Ori", "Shahar"};
	int IDs[] = {33, 30, 2, 35, 26};
	for (i = 0;i < initialSize;++i)
	{
		person = (Person*)malloc(sizeof(Person));
		strcpy(person->m_name, names[i]);
		person->m_id = IDs[i];
		VectorAppend(vector, person);
	}
	VectorDestroy(&vector, DestroyPersonElement);
	if(vector == NULL)
	{
		printf("Test Destroy Allocated Elemnts PASSED\n");
	}
	else
	{
		printf("Test Destroy Allocated Elemnts **FAILED**\n");
	}
}

/*Assiting functions:*/
void DestroyIntElement(void* _item)
{
	return;
}

int	SumVecAction(void* _element, size_t _index, void* _context)
{
	*(int*)_context += *(int*)_element;
	return 1;
}

void DestroyPersonElement(void* _item)
{
	free(_item);
	return;
}
