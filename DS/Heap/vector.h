#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct Vector Vector;

/* size - The initial allocation size.
   blockSize - The extention block size. */

/*
    Description: Makes pointer to the vector.
    Input: original size of the vector and inc_vector_block.
    Output: OK / NULL .
    ERROR: OK - Pointer successfully returned.
           NULL - new pointer=null , if size=0 && inc=0 or allocation failed.
*/   
Vector* VectorCreate (size_t _initialSize, size_t _extensionBblockSize);

/*
    Description: free dinamic allocation to the vector.
    Input: pointer to the vector.
    Output: no output.
    ERROR: no error.
*/ 
void VectorDestroy (Vector* _vector);

/*
    Description: Add item to end .
    Input: pointer to the vector and the item.
    Output: ERR_NOT_INITIALIZED / ERR_OVERFLOW / ERR_REALLOCATION_FAILED / ERR_OK.
    ERROR: ERR_NOT_INITIALIZED - if vector = NULL.
           ERR_OVERFLOW - size = block and block = 0 .
           ERR_REALLOCATION_FAILED - realloc failed .
           ERR_OK - the addition was successful.
*/
ADTErr VectorAdd (Vector *_vector ,int _item);          /* Add item to end */

/*
    Description: delete item from the end .
    Input: pointer to the vector and the int pointer.
    Output: ERR_NOT_INITIALIZED / ERR_UNDERFLOW / ERR_REALLOCATION_FAILED / ERR_OK.
    ERROR: ERR_NOT_INITIALIZED - if vector = NULL or item=NULL.
           ERR_UNDERFLOW - num of element =0 .
           ERR_OK - the remove done successful.
*/
ADTErr VectorDelete (Vector *_vector ,int* _item);      /* Delete item from the end */
/* The index range in the following functions is : 0..numOfitems-1 */

/*
    Description: entered the element in the index into int variable .
    Input: pointer to the vector , pointer to int variable and index.
    Output: ERR_OK / ERR_NOT_INITIALIZED / ERR_WORNG_INDEX.
    ERROR: ERR_OK - the element was successfully entered into the variable .
           ERR_NOT_INITIALIZED - ptr_vector = NULL .
           ERR_WORNG_INDEX - index < 0 or index >= num of element .
*/
ADTErr VectorGet(Vector *_vector, size_t _index , int *_item);

/*
    Description: set item to array in index place .
    Input: pointer to the vector , int item and index.
    Output: ERR_OK / ERR_NOT_INITIALIZED / ERR_WORNG_INDEX.
    ERROR: ERR_OK - the element was successfully entered into the variable .
           ERR_NOT_INITIALIZED - ptr_vector = NULL .
           ERR_WORNG_INDEX - index < 0 or index >= num of element .
*/
ADTErr VectorSet(Vector *_vector, size_t _index , int _item);

/*
    Description: entered number of elements into int variable .
    Input: pointer to the vector and pointer to int variable.
    Output: ERR_OK / ERR_NOT_INITIALIZED.
    ERROR: ERR_OK - the number of elements was successfully entered into the variable .
           ERR_NOT_INITIALIZED - ptr_vector = NULL .
*/ 
ADTErr VectorItemsNum(Vector *_vector , int* _numOfItems);

/* Unit-Test functions */

/*
    Description: print the vector .
    Input: pointer to the vector .
    Output: no output .
    Error: no error .
*/ 
void VectorPrint(Vector *_vector);



#endif /* __VECTOR_H__ */
