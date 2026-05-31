#include <stdlib.h>
#include "Queue.h"

struct Queue
{
	void** m_que;
	size_t m_size;
	size_t m_head; /* Index of head in m_que. */
	size_t m_tail; /* Index of tail in m_que. */
	size_t m_nItems;
};

Queue* QueueCreate (size_t _size)
{
	Queue *queue = NULL;
	void* que = NULL;
	if(_size == 0)
	{
		return NULL;
	}
	if((queue = (Queue*)malloc(sizeof(Queue))) == NULL)
	{
		return NULL;
	}
	if((que = (void**)malloc(_size * sizeof(void*))) == NULL)
	{
		free(queue);
		return NULL;
	}
	queue->m_que = que;
	queue->m_size = _size;
	queue->m_head = 0;
	queue->m_tail = 0;
	queue->m_nItems = 0;
	return queue;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy)
{
	size_t i;
	if(_queue != NULL && *_queue != NULL)
	{
		if(_itemDestroy != NULL)
		{
			for(i = 0 ; i < (*_queue)->m_nItems ; ++i)
			{
				_itemDestroy((*_queue)->m_que[i]);
			}
		}
		free((*_queue)->m_que);
		free((*_queue));
		*_queue = NULL;
	}
}

QueueResult QueueInsert(Queue* _queue, void* _item)
{
	if(_queue == NULL)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if(_item == NULL)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if(_queue->m_nItems == _queue->m_size)
	{
		return QUEUE_OVERFLOW_ERROR;
	}
	_queue->m_que[_queue->m_tail] = _item;
	_queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
	_queue->m_nItems += 1;
	return QUEUE_SUCCESS;
}

QueueResult QueueRemove(Queue* _queue, void** _item)
{
	if(_queue == NULL)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if(_item == NULL)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if(_queue->m_nItems == 0)
	{
		return QUEUE_DATA_NOT_FOUND_ERROR;
	}
	*_item = _queue->m_que[_queue->m_head];
	_queue->m_head = (_queue->m_head + 1) % _queue->m_size;
	_queue->m_nItems -= 1;
	return QUEUE_SUCCESS;
}

size_t QueueIsEmpty(Queue *_queue)
{
	if(_queue == NULL)
	{
		return 0;
	}
	return _queue->m_nItems;
}

size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context)
{
	size_t i = 0;
	if(_queue == NULL)
	{
		return i;
	}
	for(i = 0 ; i < _queue->m_nItems ; ++i)
	{
		if((_action(_queue->m_que[i], _context)) == 0)
		{
			++i;
			break;
		}
	}
	return i;
}
