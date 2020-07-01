#ifndef __POINTER_FUNC_H__
#define __POINTER_FUNC_H__

typedef int (*SortingType)(int,int);

/*
     Description : bubble sort .
     Complexity : O(n^2) .
     Input : 1) An array of integers .
             2) Array order function
     Output : ERR_OK / ERR_NOT_INITIALIZED .
     Error : ERR_OK - Successful sorting .
             ERR_NOT_INITIALIZED - One or both of the pointers is null .
*/
ADTErr BubbleSort(SortingType _func , int *_array, size_t _arrSize);

#endif /* __POINTER_FUNC_H__ */
