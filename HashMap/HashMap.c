#include <stdio.h>

#include <stdlib.h>/*for malloc*/
#include "HashMap.h"
#include "GenericDoubleLinkedList.h"
#include "list_itr.h"
#include "list_functions.h"
#define SIZE_FACTOR 1
#define MINIMUM_SIZE 1
#define CAPACITY(MAP) (MAP->m_capacity)
#define LIST(MAP, INDEX) (MAP->m_data[INDEX])

struct HashMap
{
	List** m_data;
	HashFunction m_hashFunction;
	EqualityFunction m_equalityFunction;
	size_t m_capacity; /*real hash size */
	size_t m_numOfItems; /*number of occupied places in the table*/
};

typedef struct ElementInfo
{
	void* m_key;
	void* m_value;
}ElementInfo;

typedef struct ElementDestroy
{
	KeyDestroy m_keyDestroy;
	ValDestroy m_valDestroy;
}ElementDestroy;

typedef struct KeyCompare
{
	void* m_key;
	EqualityFunction m_equalityFunction;
}KeyCompare;

typedef struct ElementForEach
{
	KeyValueActionFunction m_action;
	void* m_context;
	size_t m_counter;
}ElementForEach;

/*Assisting Functions:*/
static int MapActionDestroyTwoNotNull(void* _element, void* _context);
static void* FindKey(const HashMap* _map, const void* _key);
static int InnerPredicateFunction(void *_element, void *_keyCompare);
static size_t CalculateCapacity(size_t _size);
static size_t NextPrime(size_t _capacity);
static size_t IsPrime(size_t _capacity);
static int MapActionDestroyTwoNull(void* _element, void* _context);
static int MapActionDestroyKeyNull(void* _element, void* _context);
static int MapActionDestroyValNull(void* _element, void* _context);
static int MapActionForEach(void* _element, void* _context);

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap *newHash = NULL;
	List** newData = NULL;
	size_t newCapacity = 0;
	if(_capacity < MINIMUM_SIZE || _hashFunc == NULL || _keysEqualFunc == NULL)
	{
		return NULL;
	}
	if((newHash = (HashMap*)malloc(sizeof(HashMap))) == NULL)
	{
		return NULL;
	}
	newCapacity = CalculateCapacity(_capacity);
	if((newData = (List**)calloc(newCapacity,sizeof(List*))) == NULL)
	{
		free(newHash);
		return NULL;
	}
	newHash->m_data = newData;
	newHash->m_hashFunction = _hashFunc;
	newHash->m_equalityFunction = _keysEqualFunc;
	newHash->m_capacity = newCapacity;
	newHash->m_numOfItems = 0;
	return newHash;
}

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	size_t register index = 0;
	void *listTail = NULL, *begin = NULL;
	ElementDestroy* elementDestroy;
	if(_map == NULL || *_map == NULL)
	{
		return;
	}
	if((elementDestroy = (ElementDestroy*)malloc(sizeof(ElementDestroy))) == NULL)
	{
		return;
	}
	elementDestroy->m_keyDestroy = _keyDestroy;
	elementDestroy->m_valDestroy = _valDestroy;
	for(index = 0;index < CAPACITY((*_map));++index)
	{
		if(LIST((*_map), index) != NULL)
		{
			begin = ListItrBegin(LIST((*_map), index));
			listTail = ListItrEnd(LIST((*_map), index));
			if(_keyDestroy == NULL && _valDestroy == NULL)
			{
				ListItrForEach(begin, listTail, MapActionDestroyTwoNull, elementDestroy);
			}
			else if(_keyDestroy != NULL && _valDestroy == NULL)
			{
				ListItrForEach(begin, listTail, MapActionDestroyValNull, elementDestroy);
			}
			else if(_keyDestroy == NULL && _valDestroy != NULL)
			{
				ListItrForEach(begin, listTail, MapActionDestroyKeyNull, elementDestroy);
			}
			else
			{
				ListItrForEach(begin, listTail, MapActionDestroyTwoNotNull, elementDestroy);
			}
			
		}
		ListDestroy(&LIST((*_map), index), NULL);
	}
	free(elementDestroy);
	free((*_map)->m_data);
	free(*_map);
	*_map = NULL;
}


Map_Result HashMapInsert(HashMap* _map, const void* _key, void* _value)
{
	size_t index = 0;
	void* node = NULL, *listTail = NULL;
	ElementInfo* elementInfo = NULL;
	ListResult pushResult = 0;
	if(_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(_key == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	index = _map->m_hashFunction(_key) % CAPACITY(_map);
	if(LIST(_map, index) == NULL)/*Allocate New List*/
	{
		LIST(_map, index) = ListCreate();
		if(LIST(_map, index) == NULL)
		{
			return MAP_ALLOCATION_ERROR;
		}
	}
	else /*Check Duplicate*/
	{
		node = FindKey(_map, _key);
		if(node == NULL)
		{
			return MAP_ALLOCATION_ERROR;
		}
		listTail = ListItrEnd(LIST(_map, index));
		if(node != listTail) /*Duplicate*/
		{
			return MAP_KEY_DUPLICATE_ERROR;
		}
	}
	if((elementInfo = (ElementInfo*)malloc(sizeof(ElementInfo))) == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}
	elementInfo->m_key = (void*)_key;
	elementInfo->m_value = _value;
	pushResult = ListPushTail(LIST(_map, index), elementInfo);
	if(pushResult != LIST_SUCCESS)
	{
		free(elementInfo);
		return MAP_ALLOCATION_ERROR;
	}
	_map->m_numOfItems += 1;
	return MAP_SUCCESS;
}

Map_Result HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	size_t index = 0;
	void* node = NULL, *listTail = NULL;
	ElementInfo* elementInfo = NULL;
	if(_map == NULL || _pKey == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(_searchKey == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if(_map->m_numOfItems == 0)
	{
		return MAP_UNDERFLOW_ERROR;
	}
	node = FindKey(_map, _searchKey);
	index = _map->m_hashFunction(_searchKey) % CAPACITY(_map);
	listTail = ListItrEnd(LIST(_map, index));
	if(node == listTail)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	elementInfo = ListItrRemove(node);
	*_pKey = elementInfo->m_key;
	if(_pValue != NULL)
	{
		*_pValue = elementInfo->m_value;
	}
	free(elementInfo);
	_map->m_numOfItems -= 1;
	return MAP_SUCCESS;
}

Map_Result HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	size_t index;
	void* node = NULL, *listTail = NULL;
	ElementInfo* elementInfo = NULL;
	if(_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(_searchKey == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if(_map->m_numOfItems == 0)
	{
		return MAP_UNDERFLOW_ERROR;
	}
	node = FindKey(_map, _searchKey);
	index = _map->m_hashFunction(_searchKey) % CAPACITY(_map);
	listTail = ListItrEnd(LIST(_map, index));
	if(node == listTail)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	elementInfo = ListItrGet(node);
	if(_pValue != NULL)
	{	
		*_pValue = elementInfo->m_value;
	}
	return MAP_SUCCESS;
}

size_t HashMapSize(const HashMap* _map)
{
	if(_map == NULL)
	{
		return 0;
	}
	return _map->m_numOfItems;
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	size_t register index;
	void *begin = NULL, *listTail = NULL;
	ElementForEach elementForEach;
	if(_map == NULL || _action == NULL)
	{
		return 0;
	}
	elementForEach.m_counter = 0;
	for(index = 0;index < CAPACITY(_map);++index)
	{
		if(LIST((_map), index) != NULL)
		{
			begin = ListItrBegin(LIST((_map), index));
			listTail = ListItrEnd(LIST((_map), index));
			elementForEach.m_action = _action;
			elementForEach.m_context = _context;
			if((ListItrForEach(begin, listTail, MapActionForEach, &elementForEach)) == 0)
			{
				break;
			}
		}
	}
	return elementForEach.m_counter;
}

/*Assisting Functions:*/
static void* FindKey(const HashMap* _map, const void* _key)
{
	size_t index = 0;
	void *listFirst = NULL, *listTail = NULL, *returned;
	KeyCompare *keyCompare = NULL;
	if((keyCompare = (KeyCompare*)malloc(sizeof(KeyCompare))) == NULL)
	{
		return NULL;
	}
	keyCompare->m_key = (void*)_key;
	keyCompare->m_equalityFunction = _map->m_equalityFunction;
	index = _map->m_hashFunction(keyCompare->m_key) % CAPACITY(_map);
	listFirst = ListItrBegin(_map->m_data[index]);
	listTail = ListItrEnd(_map->m_data[index]);
	returned = ListItrFindFirst(listFirst, listTail, InnerPredicateFunction, keyCompare);
	free(keyCompare);
	return returned;
}

static int InnerPredicateFunction(void *_element, void *_keyCompare)
{
	void *key1 = ((ElementInfo*)_element)->m_key, *key2 = ((KeyCompare*)_keyCompare)->m_key;
	return ((KeyCompare*)_keyCompare)->m_equalityFunction(key1, key2);
}

static size_t CalculateCapacity(const size_t _size)
{
	size_t capacity = _size*SIZE_FACTOR;
	return NextPrime(capacity);
}

static size_t NextPrime(size_t _capacity)
{
	int found = 0;
	if(_capacity == 1)
	{
		return _capacity + 1;
	}
	while(!found)
	{
		++_capacity;
		if(IsPrime(_capacity))
		{
			break;
		}
	}
	return _capacity;
}

static size_t IsPrime(size_t _capacity)
{
	int i;
	for(i = 2;i*i <= _capacity;++i)
	{
		if(_capacity % i == 0)
		{
			return 0;
		}
	}
	return 1;
}


static int MapActionDestroyTwoNull(void* _element, void* _context)
{
	free(_element);
	return 1;
}

static int MapActionDestroyKeyNull(void* _element, void* _context)
{
	((ElementDestroy*)_context)->m_valDestroy(((ElementInfo*)_element)->m_value);
	free(_element);
	return 1;
}
static int MapActionDestroyValNull(void* _element, void* _context)
{
	((ElementDestroy*)_context)->m_keyDestroy(((ElementInfo*)_element)->m_key);
	free(_element);
	return 1;
}
static int MapActionDestroyTwoNotNull(void* _element, void* _context)
{
	((ElementDestroy*)_context)->m_keyDestroy(((ElementInfo*)_element)->m_key);
	((ElementDestroy*)_context)->m_valDestroy(((ElementInfo*)_element)->m_value);
	free(_element);
	return 1;
}

static int MapActionForEach(void* _element, void* _context)
{
	int returned;
	returned = ((ElementForEach*)_context)->m_action(((ElementInfo*)_element)->m_key, ((ElementInfo*)_element)->m_value, ((ElementForEach*)_context)->m_context);
	((ElementForEach*)_context)->m_counter += 1;
	return returned;
}
