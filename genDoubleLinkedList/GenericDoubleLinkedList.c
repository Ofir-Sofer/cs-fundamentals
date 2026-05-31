#include <stdlib.h>
#include "GenericDoubleLinkedList.h"
#include "ListInternal.h"

List* ListCreate(void)
{
	List* newList;
	newList = (List*)malloc(sizeof(List));
	if(newList == NULL)
	{
		return NULL;
	}
	newList->m_head.m_prev = &newList->m_head;
	newList->m_head.m_next = &newList->m_tail;
	newList->m_tail.m_prev = &newList->m_head;
	newList->m_tail.m_next = &newList->m_tail;
	return newList;
}

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* node = NULL, *oldNode = NULL;
	if(_pList == NULL || *_pList == NULL)
	{
		return;
	}
	node = (*_pList)->m_head.m_next;
	while(node != &(*_pList)->m_tail)
	{
		if(_elementDestroy != NULL)
		{
			_elementDestroy(node->m_data);
		}
		oldNode = node;
		node = node->m_next;
		free(oldNode);
	}
	free(*_pList);
	*_pList = NULL;
}

ListResult ListPushHead(List* _list, void* _item)
{
	Node* newNode = NULL;
	if(_list == NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_item == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		return LIST_ALLOCATION_ERROR;
	}
	newNode->m_data = _item;
	Insert(newNode, _list->m_head.m_next);
	return LIST_SUCCESS;
}

ListResult ListPushTail(List* _list, void* _item)
{
	Node* newNode = NULL;
	if(_list == NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_item == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		return LIST_ALLOCATION_ERROR;
	}
	newNode->m_data = _item;
	Insert(newNode, &_list->m_tail);
	return LIST_SUCCESS;
}

ListResult ListPopHead(List* _list, void** _pItem)
{
	void* temp;
	if(_list == NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_pItem == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return LIST_UNDER_FLOW_ERROR;
	}
	*_pItem = _list->m_head.m_next->m_data;
	temp = _list->m_head.m_next;
	Remove(_list->m_head.m_next);
	free(temp);
	return LIST_SUCCESS;
}

ListResult ListPopTail(List* _list, void** _pItem)
{
	void* temp;
	if(_list == NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_pItem == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return LIST_UNDER_FLOW_ERROR;
	}
	*_pItem = _list->m_tail.m_prev->m_data;
	temp = _list->m_tail.m_prev;
	Remove(_list->m_tail.m_prev);
	free(temp);
	return LIST_SUCCESS;
}

size_t ListSize(const List* _list)
{
	Node* node = NULL;
	size_t count;
	if(_list == NULL)
	{
		return 0;
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

/*Assiting Functions:*/
void Insert(Node* _new, Node* _rightRef)
{
	_new->m_prev = _rightRef->m_prev;
	_new->m_next = _rightRef;
	_rightRef->m_prev->m_next = _new;
	_rightRef->m_prev = _new;
}

void Remove(Node* _remove)
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

void* GetNodeDataHead(List* list)
{
	return list->m_head.m_next->m_data;
}

void* GetNodeDataTail(List* list)
{
	return list->m_tail.m_prev->m_data;
}
