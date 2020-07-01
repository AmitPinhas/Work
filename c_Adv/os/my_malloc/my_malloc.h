#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

typedef struct Pool Pool;

Pool* CreateMyMallocPool( size_t _numOfBuffer , size_t _SizeOfBuffer );

void DestroyMyMallocPool( Pool **_pool );

void* MyMalloc(Pool *_pool)

void FreeMyMalloc(Pool *_pool , void* _buffer); 

#endif /* __MY_MALLOC_H__ */
