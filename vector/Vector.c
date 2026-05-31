#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"
#include "ADTDefs.h"
#define BLOCK_SIZE_FACTOR 2
#define MAGIC_NUM 2584856

struct Vector
{
	int* m_items;
	size_t m_originalSize; /* original allocated space for items */
	size_t m_size; /* actual allocated space for items*/
	size_t m_nItems; /* actual number of items */
	size_t m_blockSize; /* the chunk size to be allocated when no space*/
	int m_magicNum;
};

/*assisting functions:*/
ADTErr CheckParams(size_t _initialSize, size_t _extensionBlockSize);
ADTErr CheckStructPtr(Vector* _vector);
ADTErr CheckIncrease(Vector *_vector);
ADTErr CheckDecrease(Vector *_vector);
ADTErr CheckIndex(Vector *_vector, size_t _index);

Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize)
{
	Vector *vectorPtr;
	int* m_items;
	ADTErr check;
	check = CheckParams(_initialSize, _extensionBlockSize);
	if (check != ERR_OK)
	{
		return NULL;
	}
	if((vectorPtr = (Vector*)malloc(sizeof(Vector))) == NULL)
	{
		return NULL;
	}
	if((m_items = (int*)malloc(_initialSize*sizeof(int))) == NULL)
	{
		free(vectorPtr);
		return NULL;
	}
	vectorPtr->m_items = m_items;
	vectorPtr->m_originalSize = _initialSize;
	vectorPtr->m_size = _initialSize;
	vectorPtr->m_nItems = 0;
	vectorPtr->m_blockSize = _extensionBlockSize;
	vectorPtr->m_magicNum = MAGIC_NUM;
	return vectorPtr;
}

void VectorDestroy(Vector* _vector)
{
	if(CheckStructPtr(_vector) != ERR_NOT_INITIALIZED && _vector->m_magicNum == MAGIC_NUM)
	{
		_vector->m_magicNum = 0;
		free(_vector->m_items);
		free(_vector);
	}
}

ADTErr VectorAdd(Vector *_vector, int _item)
{
	ADTErr result;
	if(CheckStructPtr(_vector) == ERR_NOT_INITIALIZED)
	{
		return ERR_NOT_INITIALIZED;
	}
	result = CheckIncrease(_vector);
	if (result != ERR_OK)
	{
		return result;
	}
	_vector->m_items[_vector->m_nItems] = _item;
	_vector->m_nItems += 1;	
	return result;
}

ADTErr VectorDelete(Vector *_vector, int* _item)
{
	if(CheckStructPtr(_vector) == ERR_NOT_INITIALIZED || _item==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_vector->m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	*_item = _vector->m_items[_vector->m_nItems-1];
	_vector->m_nItems -= 1;
	return CheckDecrease(_vector);
}

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
	if(CheckStructPtr(_vector) == ERR_NOT_INITIALIZED || _item == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(CheckIndex(_vector, _index) == ERR_WRONG_INDEX)
	{
		return ERR_WRONG_INDEX;
	}
	*_item = _vector->m_items[_index];
	return ERR_OK;	
}

ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
	if(CheckStructPtr(_vector) == ERR_NOT_INITIALIZED)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(CheckIndex(_vector, _index) == ERR_WRONG_INDEX)
	{
		return ERR_WRONG_INDEX;
	}
	_vector->m_items[_index] = _item;
	return ERR_OK;	
}

ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems)
{
	if(CheckStructPtr(_vector) == ERR_NOT_INITIALIZED || _numOfItems == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	*_numOfItems = _vector->m_nItems;
	return ERR_OK;
}

void VectorPrint(Vector* _vector)
{
	int i;
	if(CheckStructPtr(_vector) != ERR_NOT_INITIALIZED)
	{
		printf("Array original size=%lu, array size=%lu, number of elements=%lu, blocksize=%lu\n", _vector->m_originalSize, _vector->m_size, _vector->m_nItems, _vector->m_blockSize);
		printf("array values:\n");
		for (i = 0;i < _vector->m_nItems;++i)
		{
			printf("%d ", _vector->m_items[i]);
		}
		printf("\n");
	}	
}

ADTErr CheckParams(size_t _initialSize, size_t _extensionBlockSize)
{
	if(_initialSize == 0 && _extensionBlockSize == 0)
	{
		return ERR_WRONG_INDEX;/*PARAMS_ERROR;*/
	}
	return ERR_OK;
}

ADTErr CheckStructPtr(Vector* _vector)
{
	if (_vector == NULL || _vector->m_items == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return ERR_OK;
}

ADTErr CheckIncrease(Vector *_vector)
{
	int *tempArr = NULL;
	if (_vector->m_nItems == _vector->m_size)
	{
		if (_vector->m_blockSize == 0)
		{
			return ERR_OVERFLOW;
		}
		tempArr = (int*)realloc(_vector->m_items, (_vector->m_blockSize+_vector->m_size)*sizeof(int));
		if (tempArr == NULL)
		{
			return ERR_REALOOCATION_FAILED;
		}
		_vector->m_items = tempArr;
		_vector->m_size += _vector->m_blockSize;
	}
	return ERR_OK;
}

ADTErr CheckDecrease(Vector *_vector)
{
	int *tempArr = NULL;
	if (_vector->m_blockSize != 0 && _vector->m_size > _vector->m_originalSize &&
	_vector->m_size - _vector->m_nItems >= BLOCK_SIZE_FACTOR*_vector->m_blockSize)
	{
		tempArr = (int*)realloc(_vector->m_items, (_vector->m_size - _vector->m_blockSize)*sizeof(int));
		if (tempArr == NULL)
		{
			return ERR_REALOOCATION_FAILED;
		}
		_vector->m_items = tempArr;
		_vector->m_size -= _vector->m_blockSize;
	}
	return ERR_OK;
}

ADTErr CheckIndex(Vector *_vector, size_t _index)
{
	if (_index >= _vector->m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	return ERR_OK;
}

/*get functions:*/
size_t GetVectorSize(Vector *_vector)
{
	return _vector->m_size;
}
size_t GetVectorM_nItems(Vector *_vector)
{
	return _vector->m_nItems;
}
size_t GetVectorOriginalSize(Vector *_vector)
{
	return _vector->m_originalSize;
}
size_t GetVectorBlockSize(Vector *_vector)
{
	return _vector->m_blockSize;
}
int GetVectorMagicNum(Vector *_vector)
{
	return _vector->m_magicNum;
}
int GetVectorArrayLastValue(Vector *_vector)
{
	return _vector->m_items[_vector->m_nItems-1];
}
int GetMAGIC_NUM()
{
	return MAGIC_NUM;
}

