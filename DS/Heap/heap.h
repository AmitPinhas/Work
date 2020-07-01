#ifndef __HEAP_H__
#define __HEAP_H__

#include "vector.h"

#define ERR_PTR_NULL -1

typedef struct Heap Heap;


/*
    Description: gets a vector and turns it into a maximum heap .
    Input: pointer to the vector .
    Output: OK / NULL .
    Error: OK - the heap pointer was successfully returned .
           NULL - the pointer to the vector is null , if allocation failed .
    Complexity: O(n) .       
*/  
Heap* HeapBuild(Vector *_vec);

/*
    Description: free dinamic allocation to the heap.
    Input: pointer to the heap.
    Output: no output.
    Error: no error.
    Complexity: O(1) .
    Warning : doesn't free the vector .
*/ 
void HeapDestroy(Heap *_heap);

/*
    Description: inserting a new organ into the heap .
    Input: a) pointer to the heap.
           b) int data .
    Output: ERR_OK / ERR_NOT_INITIALIZED .
    Error: ERR_OK - the organ was successfully inserted .
           ERR_NOT_INITIALIZED - the pointer to the heap is null .
    Complexity: O(log n) .
*/
ADTErr HeapInsert(Heap *_heap , int _data);

/*
    Description: entered the max element in the heap into int variable .
    Input: a) pointer to the heap.
           b) pointer to int variable .
    Output: ERR_OK / ERR_NOT_INITIALIZED / ERR_WORNG_INDEX.
    Error: ERR_OK - the max element was successfully entered into the variable .
           ERR_NOT_INITIALIZED - one or both of the pointers is null .
           ERR_UNDERFLOW - heap is empty .
    Complexity: O(1) .       
*/
ADTErr HeapMax(Heap *_heap , int *_data);

/*
    Description: delete the max element from the heap and entered him into int variable .
    Input: a) pointer to the heap.
           b) pointer to int variable .
    Output: ERR_OK / ERR_NOT_INITIALIZED / ERR_WORNG_INDEX.
    Error: ERR_OK - the max element was successfully entered into the variable and delete from the heap .
           ERR_NOT_INITIALIZED - one or both of the pointers is null .
           ERR_UNDERFLOW - heap is empty .
    Complexity: O(log n) .       
*/
ADTErr HeapExtractMax(Heap *_heap , int *_data);

/*
    Description: returns the number of organs in the heap . 
    Input: pointer to the heap.
    Output: the number of organs in the heap / ERR_PTR_NULL(-1) .
    Error: ERR_PTR_NULL(-1)  -  pointer to heap is null
    Complexity: O(1) .
*/ 
int HeapItemsNum(Heap *_heap);

/*
    Description: print the heap .
    Input: pointer to the heap .
    Output: no output .
    Error: no error .
    Complexity: O(n) .
*/
void HeapPrint(Heap *_heap);


#endif /* __HEAP_H__ */
