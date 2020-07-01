#include <stdlib.h> /* allocation */
#include "my_malloc.h"

#define BYTE 8

typedef struct Buffer Buffer;

struct Pool{
	void* m_pool;
	size_t m_numOfBuffer;
	Buffer* m_firstBuffer;
};


struct Buffer{
	Buffer* m_nextBuffer;
};

Pool* CreateMyMallocPool( size_t _numOfBuffer , size_t _SizeOfBuffer )
{
	Pool *pool;
	
	if ( _numOfBuffer < 1 || _SizeOfBuffer < 1 )
	{
		return NULL;
	}
	
	pool = (Pool*)malloc(sizeof(Pool));
	if ( NULL == pool )
	{
		return NULL;
	}
	
	pool->m_pool = malloc(sizeof(Pool) + (_numOfBuffer * (_SizeOfBuffer+sizeof(Buffer)));
	if ( NULL == pool->m_pool )
	{
		free(pool);
		return NULL;
	}
	
	_SizeOfBuffer = (BYTE * ( _SizeOfBuffer/BYTE )) + (_SizeOfBuffer%BYTE ? 1:0 );
	
	pool->m_numOfBuffer = _numOfBuffer ;
	InitPool(pool , _numOfBuffer , _SizeOfBuffer);
	
	return pool;
	
}


void* MyMalloc(Pool *_pool)
{
	char* buffer ;
	
	if ( !_pool )
	{
		return NULL;
	}
	
	buffer = (char*)_pool->m_firstBuffer+sizeof(Buffer);
	_pool->m_firstBuffer = _pool->m_firstBuffer->m_nextBuffer;
	return (void*)(buffer+1);
}


void FreeMyMalloc(Pool *_pool , void* _buffer);
{
	char *buffer = (char*)_buffer-sizeof(Buffer);
	if ( (_pool != NULL) && (_buffer != NULL) )
	{
	_buffer->m_nextBuffer = _pool->m_firstBuffer;
	_pool->m_firstBuffer = _buffer;
	}
	return;
}

static void InitPool(Pool *_pool , size_t _numOfBuffer , size_t _SizeOfBuffer)
{
	char *buffer = (char*)_pool + sizeof(_pool);
	int totalSize =  sizeof(Buffer) +  _SizeOfBuffer;
	
	_pool->m_firstBuffer = (Buffer*)buffer;
	
	while ( _numOfBuffer-- )
	{
		((Buffer*)buffer)->m_nextBuffer = (Buffer*)(buffer + totalSize );
		(Buffer*)buffer = ((Buffer*)buffer)->m_nextBuffer;
	}
	
	((Buffer*)buffer)->m_nextBuffer = (Buffer*)_pool ;
	
	return;
}



