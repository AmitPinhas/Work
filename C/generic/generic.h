#ifndef __GENERIC_H__
#define __GENERIC_H__

#define TRUE 1
#define FALSE 0

typedef int (*CompareFunc)(void*,void*);


/*
     Description : bubble sort .
     Complexity : O(n^2) .
     Input : 1) An array  .
             2) Array order function .
             3) Size of array .
     Output : TRUE / FALSE .
     Error : TRUE - Successful sorting .
             FALSE - One or both of the pointers is null .
*/
int GBubbleSort(CompareFunc _less , void* _array[], size_t _arrSize);


#endif /* __GENERIC_H__ */
