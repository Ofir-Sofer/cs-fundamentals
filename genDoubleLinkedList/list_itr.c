#include <stdlib.h>
#include "list_itr.h"
#include "GenericDoubleLinkedList.h"
#include "ListInternal.h"
#define IS_BEGIN(_itr) (((Node*)(_itr))->m_prev->m_prev == ((Node*)(_itr))->m_prev)
#define IS_TAIL(_itr) (((Node*)(_itr))->m_next == (Node*)(_itr))

ListItr ListItrBegin(const List* _list)
{
	if(_list == NULL)
	{
		return NULL;
	}
	return (ListItr)(_list->m_head.m_next);
}

ListItr ListItrEnd(const List* _list)
{
	if(_list == NULL)
	{
		return NULL;
	}
	return (ListItr)&(_list->m_tail);
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
	return (_a == _b);
}

ListItr ListItrNext(ListItr _itr)
{
	if(_itr == NULL)
	{
		return NULL;
	}
	return (ListItr)(((Node*)_itr)->m_next);
}

ListItr ListItrPrev(ListItr _itr)
{
	if(_itr == NULL || IS_BEGIN(_itr))
	{
		return _itr;
	}
	return (ListItr)(((Node*)_itr)->m_prev);
}

void* ListItrGet(ListItr _itr)
{
	if(_itr == NULL || IS_TAIL(_itr))
	{
		return NULL;
	}
	return ((Node*)_itr)->m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
	void *oldData;
	if(_itr == NULL || IS_TAIL(_itr) || _element == NULL)
	{
		return NULL;
	}
	oldData = ((Node*)_itr)->m_data;
	((Node*)_itr)->m_data = _element;
	return oldData;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	Node *newNode = NULL;
	if(_itr == NULL || _element == NULL)
	{
		return NULL;
	}
	if((newNode = (Node*)malloc(sizeof(Node))) == NULL)
	{
		return NULL;
	}
	newNode->m_data = _element;
	Insert(newNode, ((Node*)_itr));	
	return (ListItr)newNode;
}

void* ListItrRemove(ListItr _itr)
{
	void* data;
	if(_itr == NULL)
	{
		return NULL;
	}
	Remove((Node*)_itr);
	data = ((Node*)_itr)->m_data;
	free(_itr);
	return data;
}

