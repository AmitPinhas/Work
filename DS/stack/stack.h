#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack Stack;

/*
    Description: Makes pointer to the stack.
    Input: original size and inc block.
    Output: OK / NULL .
    ERROR: OK - Pointer successfully returned.
           NULL - new pointer=null , if size=0 && inc=0 or allocation failed.
*/   
Stack* StackCreate(size_t _size , size_t _blockSize);

/*
    Description: free dinamic allocation to the stack.
    Input: pointer to the stack.
    Output: no output.
    ERROR: no error.
*/ 
void StackDestroy(Stack *_stack);

/*
    Description: Add item to top of the stack .
    Input: pointer to the stack and the item.
    Output: ERR_OK / ERR_NOT_INITIALIZED / ERR_OVERFLOW / ERR_REALLOCATION_FAILED .    
    ERROR: ERR_OK - the addition was successful.
           ERR_NOT_INITIALIZED - if stack = NULL.
           ERR_OVERFLOW - size = block and block = 0 .
           ERR_REALLOCATION_FAILED - realloc failed .
*/
ADTErr StackPush(Stack *_stack , int _item);

/*
    Description: delete item from top of the stack .
    Input: pointer to the stack and the int pointer.
    Output: ERR_OK /  ERR_NOT_INITIALIZED / ERR_UNDERFLOW .   
    ERROR: ERR_OK - the remove done successful.
           ERR_NOT_INITIALIZED - if stack = NULL or item=NULL.
           ERR_UNDERFLOW - num of element =0 .
*/
ADTErr StackPop(Stack *_stack , int *_item);

/*
    Description: get data from top of the stack.
    Input: pointer to the stack , pointer to int variable .
    Output: ERR_OK / ERR_NOT_INITIALIZED .
    ERROR: ERR_OK - the last element was successfully entered into the variable .
           ERR_NOT_INITIALIZED - stack = NULL .
           STACK_EMPTY - stack is empty
*/
ADTErr StackTop(Stack *_stack , int *_item);

/*
    Description: check if stack is empty.
    Input: pointer to the stack .
    Output: 1 / 0.
    ERROR: TRUE - stack is empty or stack = null.
           FALSE - stack no empty
*/
int StackIsEmpty(Stack *_stack);

/* Unit-Test functions */

/*
    Description: print the stack.
    Input: pointer to the stack.
    Output: no output.
    ERROR: no error.
*/ 
void StackPrint(Stack *_stack);

#endif /* __STACK_H__ */
