#include <stdio.h>
#include "HashMap.h"

/*Test Functions:*/
static void TestCreateLegit();
static void TestFalseCreate();
static void TestDestroyDouble();
static void TestInsertLegit();
static void TestInsertTwoValuesToSameIndex();
static void TestInsertNull();
static void TestInsertDuplicate();
/*static void TestInsertOverflow();*/
/*static void TestRemoveLegit();*/
/*static void TestRemoveUnderFlow();*/
/*static void TestRemoveNotFound();*/
/*static void TestFound();*/
/*static void TestNumOfItems();*/
/*static void TestCapacity();*/
/*static void TestAverageRehashes();*/
/*static void TestMaxRehashes();*/
/*static void TestRemoveItemWithSameIndex();*/
/*static void TestPrint();*/

/*Assisting Functions:*/
size_t MyHashFunction(const void* _data);
int MyEqualityFunction(void* _firstData, void* _secondData);
void PrintIntElement(void *data);

int main(void)
{
	TestCreateLegit();
	TestFalseCreate();
	TestDestroyDouble();
	TestInsertLegit();
	TestInsertTwoValuesToSameIndex();
	TestInsertNull();
	TestInsertDuplicate();
/*	TestInsertOverflow();*/
/*	TestRemoveLegit();*/
/*	TestRemoveUnderFlow();*/
/*	TestRemoveNotFound();*/
/*	TestFound();*/
/*	TestNumOfItems();*/
/*	TestCapacity();*/
/*	TestAverageRehashes();*/
/*	TestMaxRehashes();*/
/*	TestRemoveItemWithSameIndex();*/
/*	TestPrint();*/
	return 0;
}

static void TestCreateLegit()
{
	HashMap* map = NULL;
	size_t size = 5;
	map = HashMapCreate(size, MyHashFunction, MyEqualityFunction);
	if(map != NULL)
	{
		printf("Test Create Legit PASSED\n");
	}
	else
	{
		printf("Test Create Legit **FAILED**\n");
	}
	HashMapDestroy(&map, NULL, NULL);
}

static void TestFalseCreate()
{
	HashMap *map1 = NULL, *map2 = NULL, *map3 = NULL;
	size_t size = 5;
	map1 = HashMapCreate(size, NULL, MyEqualityFunction);
	map2 = HashMapCreate(size, MyHashFunction, NULL);
	map3 = HashMapCreate(0, MyHashFunction, MyEqualityFunction);
	if(map1 == NULL && map2 == NULL && map3 == NULL)
	{
		printf("Test False Create PASSED\n");
	}
	else
	{
		printf("Test False Create **FAILED**\n");
	}
}

static void TestDestroyDouble()
{
	HashMap *map = NULL;
	size_t size = 5;
	map = HashMapCreate(size, MyHashFunction, MyEqualityFunction);
	HashMapDestroy(&map, NULL, NULL);
	HashMapDestroy(&map, NULL, NULL);
	if(map == NULL)
	{
		printf("Test Double Destroy PASSED\n");
	}
	else
	{
		printf("Test Double Destroy **FAILED**\n");
	}
}

static void TestInsertLegit()
{
	HashMap *map = NULL;
	size_t size = 5;
	int data = 478, key = 2;
	Map_Result returned;
	map = HashMapCreate(size, MyHashFunction, MyEqualityFunction);
	returned = HashMapInsert(map, &key, &data);
	if(returned == MAP_SUCCESS && HashMapSize(map) == 1)
	{
		printf("Test Insert Legit PASSED\n");
	}
	else
	{
		printf("Test Insert Legit **FAILED**\n");
	}
	HashMapDestroy(&map, NULL, NULL);
}

static void TestInsertTwoValuesToSameIndex()
{
	HashMap *map = NULL;
	size_t size = 5;
	int data1 = 478, key1 = 2, data2 = 3782, key2 = 7;
	Map_Result returned;
	map = HashMapCreate(size, MyHashFunction, MyEqualityFunction);
	returned = HashMapInsert(map, &key1, &data1);
	returned = HashMapInsert(map, &key2, &data2);
	if(returned == MAP_SUCCESS && HashMapSize(map) == 2)
	{
		printf("Test Insert Two Values To Same Index PASSED\n");
	}
	else
	{
		printf("Test Insert Two Values To Same Index **FAILED**\n");
	}
	HashMapDestroy(&map, NULL, NULL);
}

static void TestInsertNull()
{
	HashMap *map = NULL;
	size_t size = 5;
	int data = 478, key = 2;
	Map_Result returned1, returned2;
	map = HashMapCreate(size, MyHashFunction, MyEqualityFunction);
	returned1 = HashMapInsert(NULL, &key, &data);
	returned2 = HashMapInsert(map, NULL, &data);
	if(returned1 == MAP_UNINITIALIZED_ERROR && returned2 == MAP_KEY_NULL_ERROR)
	{
		printf("Test Insert Null PASSED\n");
	}
	else
	{
		printf("Test Insert Null **FAILED**\n");
	}
	HashMapDestroy(&map, NULL, NULL);
}

static void TestInsertDuplicate()
{
	HashMap *map = NULL;
	size_t size = 5;
	int data = 478, key = 2;
	Map_Result returned;
	map = HashMapCreate(size, MyHashFunction, MyEqualityFunction);
	returned = HashMapInsert(map, &key, &data);
	returned = HashMapInsert(map, &key, &data);
	if(returned == MAP_KEY_DUPLICATE_ERROR)
	{
		printf("Test Insert Duplicate PASSED\n");
	}
	else
	{
		printf("Test Insert Duplicate **FAILED**\n");
	}
	HashMapDestroy(&map, NULL, NULL);
}

/*static void TestInsertOverflow()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 1;*/
/*	int data = 478;*/
/*	HashSet_Result returned;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned = HashInsert(hash, &data);*/
/*	returned = HashInsert(hash, &data);*/
/*	if(returned == SET_OVERFLOW)*/
/*	{*/
/*		printf("Test Insert Overflow PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Insert Overflow **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestRemoveLegit()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data = 478, *storedData;*/
/*	HashSet_Result returned;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned = HashInsert(hash, &data);*/
/*	returned = HashRemove(hash, &data, (void**)&storedData);*/
/*	if(returned == SET_SUCCESS && HashNumOfItems(hash) == 0 && *storedData == data)*/
/*	{*/
/*		printf("Test Remove Legit PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Remove Legit **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestRemoveUnderFlow()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data = 478, *storedData;*/
/*	HashSet_Result returned;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned = HashRemove(hash, &data, (void**)&storedData);*/
/*	if(returned == SET_UNDERFLOW && HashNumOfItems(hash) == 0)*/
/*	{*/
/*		printf("Test Remove Under Flow PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Remove Under Flow **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestRemoveNotFound()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data = 478, data2 = 57834, *storedData;*/
/*	HashSet_Result returned;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned = HashInsert(hash, &data);*/
/*	returned = HashRemove(hash, &data2, (void**)&storedData);*/
/*	if(returned == SET_KEY_NOT_FOUND && HashNumOfItems(hash) == 1)*/
/*	{*/
/*		printf("Test Remove Not Found PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Remove Not Found **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestFound()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data = 478, data2 = 57834;*/
/*	HashSet_Result returned1, returned2;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned1 = HashInsert(hash, &data);*/
/*	returned1 = HashIsFound(hash, &data);*/
/*	returned2 = HashIsFound(hash, &data2);*/
/*	if(returned1 && !returned2)*/
/*	{*/
/*		printf("Test Found PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Found **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestNumOfItems()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data1 = 478, data2 = 57834;*/
/*	size_t returned1, returned2;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned1 = HashNumOfItems(hash);*/
/*	HashInsert(hash, &data1);*/
/*	HashInsert(hash, &data2);*/
/*	returned2 = HashNumOfItems(hash);*/
/*	if(returned1 == 0 && returned2 == 2)*/
/*	{*/
/*		printf("Test Num Of Items PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Num Of Items **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestCapacity()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data1 = 478, data2 = 57834;*/
/*	size_t returned1, returned2;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned1 = HashCapacity(hash);*/
/*	HashInsert(hash, &data1);*/
/*	HashInsert(hash, &data2);*/
/*	returned2 = HashCapacity(hash);*/
/*	if(returned1 == 5 && returned2 == 5)*/
/*	{*/
/*		printf("Test Capacity PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Capacity **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestAverageRehashes()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data1 = 3, data2 = 10;*/
/*	double returned1, returned2;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned1 = HashAverageRehashes(hash);*/
/*	HashInsert(hash, &data1);*/
/*	HashInsert(hash, &data2);*/
/*	returned2 = HashAverageRehashes(hash);*/
/*	if(returned1 == 0 && returned2 == 0.5)*/
/*	{*/
/*		printf("Test Average Rehashes PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Average Rehashes **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestMaxRehashes()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data1 = 3, data2 = 10;*/
/*	double returned1, returned2;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	returned1 = HashMaxReHash(hash);*/
/*	HashInsert(hash, &data1);*/
/*	HashInsert(hash, &data2);*/
/*	returned2 = HashMaxReHash(hash);*/
/*	if(returned1 == 0 && returned2 == 1)*/
/*	{*/
/*		printf("Test Max Rehashes PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Max Rehashes **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestRemoveItemWithSameIndex()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data1 = 3, data2 = 5, *storedData;*/
/*	HashSet_Result returned;*/
/*	size_t num1, num2;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	HashInsert(hash, &data1);*/
/*	HashInsert(hash, &data2);*/
/*	num1 = HashNumOfItems(hash);*/
/*	returned = HashRemove(hash, &data2, (void**)&storedData);*/
/*	num2 = HashNumOfItems(hash);*/
/*	if(returned == SET_SUCCESS && *storedData == data2 && num1 == 2 && num2 == 1)*/
/*	{*/
/*		printf("Test Remove Item With Same Index PASSED\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("Test Remove Item With Same Index **FAILED**\n");*/
/*	}*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*static void TestPrint()*/
/*{*/
/*	Hash* hash = NULL;*/
/*	size_t size = 5;*/
/*	int data1 = 478, data2 = 57834;*/
/*	hash = HashCreate(size, MyHashFunction, MyEqualityFunction);*/
/*	HashInsert(hash, &data1);*/
/*	HashInsert(hash, &data2);*/
/*	HashPrint(hash, PrintIntElement);*/
/*	printf("\n");*/
/*	HashDestroy(&hash, NULL);*/
/*}*/

/*Assisting Functions:*/

size_t MyHashFunction(const void* _data)
{
	return *(int*)_data*2;
}

int MyEqualityFunction(void* _element, void* _context)
{
	return (*(int*)_element == *(int*)_context);
}

void PrintIntElement(void *data)
{
	printf("%d, ", *(int*)data);
}
