#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"
#define MAGIC_NUM 159357

typedef struct Node
{
	int m_data;
	struct Node* m_next;
	struct Node* m_prev;
}Node;

struct List
{
	Node m_head;
	Node m_tail;
	int m_magicNum;
};

/*Assiting Functions:*/
void Insert(Node* _new, Node* _rightRef);
void Remove(Node* _remove);



List* ListCreate(void)
{
	List* newList;
	newList = (List*)malloc(sizeof(List));
	if(newList == NULL)
	{
		return NULL;
	}
	newList->m_head.m_prev = NULL;
	newList->m_head.m_next = &newList->m_tail;
	newList->m_tail.m_prev = &newList->m_head;
	newList->m_tail.m_next = NULL;
	newList->m_magicNum = MAGIC_NUM;
	return newList;
}

void ListDestroy(List* _list)
{
	Node* node = NULL, *oldNode = NULL;
	if(_list == NULL || _list->m_magicNum != MAGIC_NUM)
	{
		return;
	}
	node = _list->m_head.m_next;
	while(node != &_list->m_tail)
	{
		oldNode = node;
		node = node->m_next;
		free(oldNode);
		
	}
	_list->m_magicNum = 0;
	free(_list);
}

ADTErr ListPushHead(List* _list, int _data)
{
	Node* newNode = NULL;
	if(_list == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		ERR_ALOCATION_FAILED;
	}
	newNode->m_data = _data;
	Insert(newNode, _list->m_head.m_next);
	return ERR_OK;
}

ADTErr ListPushTail(List* _list, int _data)
{
	Node* newNode = NULL;
	if(_list == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		ERR_ALOCATION_FAILED;
	}
	newNode->m_data = _data;
	Insert(newNode, &_list->m_tail);
	return ERR_OK;
}

ADTErr ListPopHead(List* _list, int* _data)
{
	Node* newNode = NULL;
	if(_list == NULL || _data == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return ERR_LIST_EMPTY;
	}
	*_data = _list->m_head.m_next->m_data;
	newNode = _list->m_head.m_next;
	Remove(_list->m_head.m_next);
	free(newNode);
	return ERR_OK;
}

ADTErr ListPopTail(List* _list, int* _data)
{
	Node* removeNode = NULL;
	if(_list == NULL || _data == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return ERR_LIST_EMPTY;
	}
	*_data = _list->m_tail.m_prev->m_data;
	newNode = _list->m_head.m_next;
	Remove(_list->m_tail.m_prev);
	free(newNode);
	return ERR_OK;
}

size_t ListCountItems(List* _list)
{
	Node* node = NULL;
	size_t count;
	if(_list == NULL)
	{
		return FALSE;
	}
	node = _list->m_head.m_next;
	count = 0; /*Not considering head and tail*/
	while(node != &_list->m_tail)
	{
		count += 1;
		node = node->m_next;	
	}	
	return count;
}

ADTErr ListIsEmpty(List* _list)
{
	if(_list == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return TRUE;
	}
	return FALSE;
}

void ListPrint(List* _list)
{
	Node* node = NULL, *oldNode = NULL;
	if(_list == NULL)
	{
		return;
	}
	node = _list->m_head.m_next;
	while(node != &_list->m_tail)
	{
		printf("%d ", node->m_data);
		node = node->m_next;
	}
	printf("\n");
	
}

/*Assiting Functions:*/
static void Insert(Node* _new, Node* _rightRef)
{
	_new->m_prev = _rightRef->m_prev;
	_new->m_next = _rightRef;
	_rightRef->m_prev->m_next = _new;
	_rightRef->m_prev = _new;
}

static void Remove(Node* _remove)
{
	_remove->m_next->m_prev = _remove->m_prev;
	_remove->m_prev->m_next = _remove->m_next;
}

/*Get Functions:*/
Node* GetHeadPrev(List* list)
{
	return list->m_head.m_prev;
}

Node* GetHeadNext(List* list)
{
	return list->m_head.m_next;
}

Node* GetHeadAdress(List* list)
{
	return &list->m_head;
}

Node* GetTailPrev(List* list)
{
	return list->m_tail.m_prev;
}

Node* GetTailNext(List* list)
{
	return list->m_tail.m_next;
}

Node* GetTailAdress(List* list)
{
	return &list->m_tail;
}

int GetNodeDataHead(List* list)
{
	return list->m_head.m_next->m_data;
}

int GetNodeDataTail(List* list)
{
	return list->m_tail.m_prev->m_data;
}

int GetMagicNumDef()
{
	return MAGIC_NUM;
}

int GetListMagicNum(List* list)
{
	return list->m_magicNum;
}
