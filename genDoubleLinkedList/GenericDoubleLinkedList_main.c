#include <stdio.h>
#include <stdlib.h>
#include "GenericDoubleLinkedList.h"
#include "list_itr.h"
#include "list_functions.h"

typedef struct Node Node;

/*Test Functions:*/
void TestCreateLegit();
void TestDestroyEmptyLegit();
void TestDestroyLegit();
void TestDestroyDouble();
void TestPushHeadLegit();
void TestPushTailLegit();
void TestPopHeadLegit();
void TestPopTailLegit();
void TestPushHeadPopTail();
void TestPushTailPopHead();
void TestPushHeadNull();
void TestPushTailNull();
void TestPopHeadUnderFlow();
void TestPopTailUnderFlow();
void TestCountLegit();
void TestDestroyAllocatedElements();

/*itr Test Functions:*/
void TestItrNullInput();
void TestItrBegin();
void TestItrEnd();
void TestItrEqualsTrue();
void TestItrEqualsFalse();
void TestItrNext();
void TestItrGetData();
void TestItrSetData();
void TestItrInsertBefore();
void TestItrRemove();

/*itr_functions Test Functions:*/
void TestItrFunctionNullInputs();
void TestItrFindFirst();
void TestItrCountIF();
void TestItrForEach();

/*Get Funtions:*/
Node* GetHeadPrev(List* list);
Node* GetHeadNext(List* list);
Node* GetHeadAdress(List* list);
Node* GetTailPrev(List* list);
Node* GetTailNext(List* list);
Node* GetTailAdress(List* list);
void* GetNodeDataHead(List* list);
void* GetNodeDataTail(List* list);

/*Assiting Functions:*/
static void DestroyListElement(void *_list);
int IntPredicate(void * _element, void* _context);
int ForEachAction(void * _element, void* _context);

int main(void)
{
	TestCreateLegit();
	TestDestroyEmptyLegit();
	TestDestroyLegit();
	TestDestroyDouble();
	TestPushHeadLegit();
	TestPushTailLegit();
	TestPopHeadLegit();
	TestPopTailLegit();
	TestPushHeadPopTail();
	TestPushTailPopHead();
	TestPushHeadNull();
	TestPushTailNull();
	TestPopHeadUnderFlow();
	TestPopTailUnderFlow();
	TestCountLegit();
	TestDestroyAllocatedElements();
	
	/*itr Test Functions:*/
	TestItrNullInput();
	TestItrBegin();
	TestItrEnd();
	TestItrEqualsTrue();
	TestItrEqualsFalse();
	TestItrNext();
	TestItrGetData();
	TestItrSetData();
	TestItrInsertBefore();
	TestItrRemove();
	
	/*itr_functions Test Functions:*/
	TestItrFunctionNullInputs();
	TestItrFindFirst();
	TestItrCountIF();
	TestItrForEach();
	return 1;
}

void TestCreateLegit()
{
	List* list = NULL; 
	list = ListCreate();
	if(GetHeadNext(list) == GetTailAdress(list) && GetTailPrev(list) == GetHeadAdress(list) && GetHeadPrev(list) == GetHeadAdress(list) && GetTailNext(list) == GetTailAdress(list))
	{
		printf("Test Create Legit PASSED\n");
	}
	else
	{
		printf("Test Create Legit **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestDestroyEmptyLegit()
{
	List* list = NULL; 
	list = ListCreate();
	ListDestroy(&list, NULL);
	if(list == NULL)
	{
		printf("Test Destroy Empty Legit PASSED\n");
	}
	else
	{
		printf("Test Destroy Empty Legit **Failed**\n");
	}
}

void TestDestroyLegit()
{
	List* list = NULL;
	int data = 8426;
	list = ListCreate();
	ListPushHead(list, &data);
	ListDestroy(&list, NULL);
	if(list == NULL)
	{
		printf("Test Destroy Legit PASSED\n");
	}
	else
	{
		printf("Test Destroy Legit **Failed**\n");
	}
}

void TestDestroyDouble()
{
	List* list = NULL;
	list = ListCreate();
	ListDestroy(&list, NULL);
	ListDestroy(&list, NULL);
	if(list == NULL)
	{
		printf("Test Destroy Double PASSED\n");
	}
	else
	{
		printf("Test Destroy Double **Failed**\n");
	}
}

void TestPushHeadLegit()
{
	List* list = NULL; 
	ListResult returned;
	int data = 8426;
	void* nodeData;
	list = ListCreate();
	returned = ListPushHead(list, &data);
	nodeData = GetNodeDataHead(list);
	if(*(int*)nodeData == data && returned == LIST_SUCCESS)
	{
		printf("Test Push Head Legit PASSED\n");
	}
	else
	{
		printf("Test Push Head Legit **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPushTailLegit()
{
	List* list = NULL; 
	ListResult returned;
	int data = 8426;
	void* nodeData;
	list = ListCreate();
	returned = ListPushTail(list, &data);
	nodeData = GetNodeDataTail(list);
	if(*(int*)nodeData == data && returned == LIST_SUCCESS)
	{
		printf("Test Push Tail Legit PASSED\n");
	}
	else
	{
		printf("Test Push Tail Legit **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPopHeadLegit()
{
	List* list = NULL; 
	ListResult returned;
	int data = 8426, *popData;
	void* nodeData;
	list = ListCreate();
	ListPushHead(list, &data);
	nodeData = GetNodeDataHead(list);
	returned = ListPopHead(list, (void**)&popData);
	if(*(int*)nodeData == *popData && returned == LIST_SUCCESS)
	{
		printf("Test Pop Head Legit PASSED\n");
	}
	else
	{
		printf("Test Pop Head Legit **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPopTailLegit()
{
	List* list = NULL; 
	ListResult returned;
	int data = 8426, *popData;
	void* nodeData;
	list = ListCreate();
	ListPushTail(list, &data);
	nodeData = GetNodeDataTail(list);
	returned = ListPopTail(list, (void**)&popData);
	if(*(int*)nodeData == *popData && returned == LIST_SUCCESS)
	{
		printf("Test Pop Tail Legit PASSED\n");
	}
	else
	{
		printf("Test Pop Tail Legit **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPushHeadPopTail()
{
	List* list = NULL;
	int data = 8426, *popData;
	void* nodeData;
	list = ListCreate();
	ListPushHead(list, &data);
	nodeData = GetNodeDataHead(list);
	ListPopTail(list, (void**)&popData);
	if(*(int*)nodeData == *popData && *popData == data)
	{
		printf("Test Push Head Pop Tail PASSED\n");
	}
	else
	{
		printf("Test Push Head Pop Tail **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPushTailPopHead()
{
	List* list = NULL; 
	int data = 8426, *popData;
	void* nodeData;
	list = ListCreate();
	ListPushTail(list, &data);
	nodeData = GetNodeDataTail(list);
	ListPopHead(list, (void**)&popData);
	if(*(int*)nodeData == *popData && *popData == data)
	{
		printf("Test Push Tail Pop Head PASSED\n");
	}
	else
	{
		printf("Test Push Tail Pop Head **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPushHeadNull()
{
	List* list = NULL; 
	ListResult returned;
	int *data = NULL;
	list = ListCreate();
	returned = ListPushHead(list, data);
	if(returned == LIST_NULL_ELEMENT_ERROR)
	{
		printf("Test Push Head Null PASSED\n");
	}
	else
	{
		printf("Test Push Head Null **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPushTailNull()
{
	List* list = NULL; 
	ListResult returned;
	int *data = NULL;
	list = ListCreate();
	returned = ListPushTail(list, data);
	if(returned == LIST_NULL_ELEMENT_ERROR)
	{
		printf("Test Push Tail Null PASSED\n");
	}
	else
	{
		printf("Test Push Tail Null **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPopHeadUnderFlow()
{
	List* list = NULL;
	void* item;
	list = ListCreate();
	if(ListPopHead(list, &item) == LIST_UNDER_FLOW_ERROR)
	{
		printf("Test Pop Head Under Flow PASSED\n");
	}
	else
	{
		printf("Test Pop Head Under Flow **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestPopTailUnderFlow()
{
	List* list = NULL;
	void* item;
	list = ListCreate();
	if(ListPopTail(list, &item) == LIST_UNDER_FLOW_ERROR)
	{
		printf("Test Pop Tail Under Flow PASSED\n");
	}
	else
	{
		printf("Test Pop Tail Under Flow **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestCountLegit()
{
	List* list = NULL; 
	size_t count1, count2;
	int data = 8426;
	list = ListCreate();
	count1 = ListSize(list);
	ListPushHead(list, &data);
	count2 = ListSize(list);
	if(count1 == 0 && count2 == 1)
	{
		printf("Test Count Legit PASSED\n");
	}
	else
	{
		printf("Test Count Legit **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestDestroyAllocatedElements()
{
	List *list1 = NULL, *list2 = NULL, *list3 = NULL;
	int data = 8426;
	list1 = ListCreate();
	ListPushHead(list1, &data);
	list2 = ListCreate();
	list3 = ListCreate();
	ListPushHead(list3, &list1);/*Create a list of pointers to list*/
	ListPushHead(list3, &list2);
	ListDestroy(&list3, DestroyListElement);
	if(list1 == NULL && list2 == NULL && list3 == NULL)
	{
		printf("Test Destroy Allocated Elements PASSED\n");
	}
	else
	{
		printf("Test Destroy Allocated Elements **Failed**\n");
	}
}

/*itr Test Functions:*/
void TestItrNullInput()
{
	List *list = NULL;
	ListItr itr = NULL;
	int return1, return2, return3, return4, return5, return6, return7, return8, data = 5;
	return1 = (ListItrBegin(list) == NULL);
	return2 = (ListItrEnd(list) == NULL);
	return3 = (ListItrNext(itr) == NULL);
	return4 = (ListItrPrev(itr) == NULL);
	return5 = (ListItrGet(itr) == NULL);
	return6 = (ListItrSet(itr, &data) == NULL);
	return7 = (ListItrInsertBefore(itr, &data) == NULL);
	return8 = (ListItrRemove(itr) == NULL);
	if(return1 && return2 && return3 && return4 && return5 && return6 && return7 && return8)
	{
		printf("Test Itr Null Input PASSED\n");
	}
	else
	{
		printf("Test Itr Null Input **Failed**\n");
	}
}

void TestItrBegin()
{
	List* list = NULL; 
	int data = 8426;
	void* nodeData;
	list = ListCreate();
	ListPushHead(list, &data);
	nodeData = ListItrBegin(list);
	if(nodeData == GetHeadNext(list))
	{
		printf("Test Itr Begin PASSED\n");
	}
	else
	{
		printf("Test Itr Begin **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrEnd()
{
	List* list = NULL; 
	int data = 8426;
	void* nodeData;
	list = ListCreate();
	ListPushHead(list, &data);
	nodeData = ListItrEnd(list);
	if(nodeData == GetTailAdress(list))
	{
		printf("Test Itr End PASSED\n");
	}
	else
	{
		printf("Test Itr End **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrEqualsTrue()
{
	List* list = NULL; 
	int data = 8426;
	void *nodeData1, *nodeData2;
	list = ListCreate();
	ListPushHead(list, &data);
	nodeData1 = ListItrBegin(list);
	nodeData2 = ListItrBegin(list);
	if(ListItrEquals(nodeData1, nodeData2))
	{
		printf("Test Itr Equals True PASSED\n");
	}
	else
	{
		printf("Test Itr Equals True **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrEqualsFalse()
{
	List* list = NULL; 
	int data1 = 8426, data2 = 45873;
	void *nodeData1, *nodeData2;
	list = ListCreate();
	ListPushHead(list, &data1);
	nodeData1 = ListItrBegin(list);
	ListPushHead(list, &data2);
	nodeData2 = ListItrBegin(list);
	if(!ListItrEquals(nodeData1, nodeData2))
	{
		printf("Test Itr Equals False PASSED\n");
	}
	else
	{
		printf("Test Itr Equals False **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrNext()
{
	List* list = NULL; 
	int data1 = 8426, data2 = 45873;
	void *nodeData1, *nodeData2;
	list = ListCreate();
	ListPushHead(list, &data1);
	nodeData1 = ListItrBegin(list);
	ListPushHead(list, &data2);
	nodeData2 = ListItrBegin(list);
	if(ListItrNext(nodeData2) == nodeData1)
	{
		printf("Test Itr Next PASSED\n");
	}
	else
	{
		printf("Test Itr Next **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrGetData()
{
	List* list = NULL; 
	int data = 8426;
	void *nodeData, *node;
	list = ListCreate();
	ListPushHead(list, &data);
	node = ListItrBegin(list);
	nodeData = ListItrGet(node);
	if(*(int*)nodeData == data)
	{
		printf("Test Itr Get Data PASSED\n");
	}
	else
	{
		printf("Test Itr Get Data **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrSetData()
{
	List* list = NULL; 
	int dataToAdd = 8426, dataToSet = 478, *oldData;
	void *nodeData, *node;
	list = ListCreate();
	ListPushHead(list, &dataToAdd);
	node = ListItrBegin(list);
	oldData = ListItrSet(node, &dataToSet);
	nodeData = ListItrGet(node);
	if(*oldData == dataToAdd && *(int*)nodeData == dataToSet)
	{
		printf("Test Itr Set Data PASSED\n");
	}
	else
	{
		printf("Test Itr Set Data **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrInsertBefore()
{
	List* list = NULL; 
	int data1 = 8426, data2 = 578, *newNodeData;
	void* nodeData, *newNode;
	list = ListCreate();
	ListPushHead(list, &data1);
	nodeData = ListItrBegin(list);
	newNode = ListItrInsertBefore(nodeData, &data2);
	newNodeData = ListItrGet(newNode);
	if(*(int*)newNodeData == data2)
	{
		printf("Test Itr Insert Before PASSED\n");
	}
	else
	{
		printf("Test Itr Insert Before **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrRemove()
{
	List* list = NULL; 
	int data = 8426, *retrievedData;
	void* nodeData;
	list = ListCreate();
	ListPushHead(list, &data);
	nodeData = ListItrBegin(list);
	retrievedData = ListItrRemove(nodeData);
	if(*retrievedData == data && ListItrBegin(list) == ListItrEnd(list))
	{
		printf("Test Itr Remove PASSED\n");
	}
	else
	{
		printf("Test Itr Remove **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

/*itr_functions Test Functions:*/
void TestItrFunctionNullInputs()
{
	List* list = NULL; 
	int data = 8426;
	void *test1, *test2, *test3, *test4, *test5, *test6;
	size_t test7, test8, test9;
	list = ListCreate();
	ListPushHead(list, &data);
	test1 = ListItrFindFirst(NULL, ListItrEnd(list), IntPredicate, &data);
	test2 = ListItrFindFirst(ListItrBegin(list), NULL, IntPredicate, &data);
	test3 = ListItrFindFirst(ListItrBegin(list), ListItrEnd(list), NULL, &data);
	test4 = ListItrForEach(NULL, ListItrEnd(list), ForEachAction, &data);
	test5 = ListItrForEach(ListItrBegin(list), NULL, ForEachAction, &data);
	test6 = ListItrForEach(ListItrBegin(list), ListItrEnd(list), NULL, &data);
	test7 = ListItrCountIf(NULL, ListItrEnd(list), IntPredicate, &data);
	test8 = ListItrCountIf(ListItrBegin(list), NULL, IntPredicate, &data);
	test9 = ListItrCountIf(ListItrBegin(list), ListItrEnd(list), NULL, &data);
	if(test1 == NULL && test2 == NULL && test3 == NULL && test4 == NULL && test5 == NULL && test6 == NULL && test7 == 0 && test8 == 0 && test9 == 0)
	{
		printf("Test Itr Function Null Inputs PASSED\n");
	}
	else
	{
		printf("Test Itr Function Null Inputs **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrFindFirst()
{
	List* list = NULL; 
	int data1 = 8426, data2 = 7843, data3 = 75438;
	void* node1, *node2;
	list = ListCreate();
	ListPushHead(list, &data1);
	ListPushHead(list, &data2);
	node1 = ListItrFindFirst(ListItrBegin(list), ListItrEnd(list), IntPredicate, &data3);
	ListPushHead(list, &data3);
	node2 = ListItrFindFirst(ListItrBegin(list), ListItrEnd(list), IntPredicate, &data3);
	if(node1 == ListItrEnd(list) && node2 == ListItrBegin(list))
	{
		printf("Test Itr Function Find PASSED\n");
	}
	else
	{
		printf("Test Itr Function Find **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrCountIF()
{
	List* list = NULL; 
	int data1 = 4534, data2 = 75438, data3 = 75438, data4 = 75438;
	size_t count1, count2;
	list = ListCreate();
	ListPushHead(list, &data1);
	count1 = ListItrCountIf(ListItrBegin(list), ListItrEnd(list), IntPredicate, &data3);
	ListPushHead(list, &data2);
	ListPushHead(list, &data3);
	ListPushHead(list, &data4);
	count2 = ListItrCountIf(ListItrBegin(list), ListItrEnd(list), IntPredicate, &data3);
	if(count1 == 0 && count2 == 3)
	{
		printf("Test Itr Function Count PASSED\n");
	}
	else
	{
		printf("Test Itr Function Count **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

void TestItrForEach()
{
	List* list = NULL; 
	int data[] = {8426, 8426, 8426, 8426};
	void* node;
	list = ListCreate();
	ListPushHead(list, &data[0]);
	ListPushHead(list, &data[1]);
	ListPushHead(list, &data[2]);
	ListPushHead(list, &data[3]);
	node = ListItrForEach(ListItrBegin(list), ListItrEnd(list), ForEachAction, &data[0]);
	if(node == ListItrEnd(list))
	{
		printf("Test Itr Function For Each PASSED\n");
	}
	else
	{
		printf("Test Itr Function For Each **Failed**\n");
	}
	ListDestroy(&list, NULL);
}

/*Assiting Functions:*/

static void DestroyListElement(void *_list)
{
	ListDestroy((List**)_list, NULL);
}

int IntPredicate(void * _element, void* _context)
{
	return *(int*)_element == *(int*)_context;
}

int ForEachAction(void * _element, void* _context)
{
	return *(int*)_element == *(int*)_context;
}
