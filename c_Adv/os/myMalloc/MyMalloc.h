#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__

/**
*  @file list.h
*  @brief Create a Generic Double Linked List data type
*
*  @details Implemented as double linked list using head and tail sentinels.
*  Nodes are allocated from heap an store pointer to user proveded element.
*
*  @author Author amitP (amitenav@gmail.com)
*
*  @bug No known bugs.
*/

#include <stddef.h>  /* size_t */

typedef struct Pool Pool;
typedef struct Node Node;

typedef enum PoolResult {
	POOL_SUCCESS = 0,
	POOL_UNINITIALIZED_ERROR,			/**< Uninitialized list 					 	*/
	POOL_ALLOCATION_ERROR,				/**< Node allocation failed due to heap error   */
	POOL_NULL_ELEMENT_ERROR,
	POOL_OVERFLOW
	/* Add more as needed by your implementation */

} PoolResult;

/**
* @brief Create a pool
*	@param[in] number of buffers
* @ param{in] size of Buffer
* @returns a pointer to the created Pool.
* @retval NULL on failure due to allocation failure
*/
void* MyMallocPoolCreate(size_t _numOfBuffers, size_t _sizeOfBuffer);

/**
* @brief Destroy pool
* @details Destroys the list completely
*
*/
void MyMallocDestroy(Pool** _pool);

/**
* @brief allocate one buffer
*
* @return poinetr to one buffer of
*/
void* MyMallocAllocateBuffer(Pool* _pool);

/**
* @brief free buffer to my pool
*
* @params _pool
* @params _buffer
* @retutn status
*
* @warnings pointer of buffer have been allocated
*/
PoolResult MyMallocFreeBuffer(Pool* _pool, void* _buffer);





#endif 
