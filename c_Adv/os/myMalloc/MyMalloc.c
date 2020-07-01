#include <stdio.h>
#include <stdlib.h> /* allocation */

#include "MyMalloc.h"
struct Node
{
	Node* m_next;
};

struct Pool
{
	size_t m_numberBuffers;
	size_t m_sizeOfBuffer;
	size_t m_freeBuffers;
	Node m_head;
};


static void InitPool(Pool* _pool)
{
	char* nextNode = (char*)_pool + sizeof(_pool);
	int numberBuffers = _pool->m_numberBuffers;
	int size = _pool->m_sizeOfBuffer + sizeof(Node);

	_pool->m_head.m_next = (Node*)nextNode;

	while (numberBuffers!=-1)
	{
		((Node*)nextNode)->m_next = (Node*)(nextNode + size);
		(Node*)nextNode = ((Node*)nextNode)->m_next;
		numberBuffers--;
	}

	((Node*)nextNode)->m_next = _pool->m_head.m_next;
}

void* MyMallocPoolCreate(size_t _numOfBuffers, size_t _sizeOfBuffer)
{
	Pool* ptr;
	int size = sizeof(Pool);
	if (0 == _numOfBuffers || 0 == _sizeOfBuffer)
	{
		return NULL;
	}
	ptr = (Pool*)malloc(sizeof(Pool) + _numOfBuffers*(sizeof(Node) + _sizeOfBuffer));
	if (NULL == ptr)
	{
		return NULL;
	}
	ptr->m_numberBuffers = _numOfBuffers;
	ptr->m_freeBuffers = _numOfBuffers;
	ptr->m_sizeOfBuffer = _sizeOfBuffer;
	InitPool(ptr);
	return ptr;
}

void MyMallocDestroy(Pool** _pool)
{
	if (NULL == _pool || NULL == *_pool)
	{
		return;
	}
	free(*_pool);
	*_pool = NULL;
}

void* MyMallocAllocateBuffer(Pool* _pool)
{
	char* Buffer;
	Node* ptr;
	if (!_pool)
	{
		return NULL;
	}
	Buffer = (char*)_pool->m_head.m_next;
	_pool->m_head.m_next = _pool->m_head.m_next->m_next;
	((Node*)Buffer)->m_next = _pool->m_head.m_next;
	return (void*)(Buffer+sizeof(Node));
}

PoolResult MyMallocFreeBuffer(Pool* _pool, void* _buffer)
{
	char* Buffer = (char*)_buffer - sizeof(Node);
	if (NULL == _pool || NULL == _buffer)
	{
		POOL_UNINITIALIZED_ERROR;
	}
	((Node*)Buffer)->m_next = _pool->m_head.m_next;
	_pool->m_head.m_next = (Node*)Buffer;
	return POOL_SUCCESS;
}
