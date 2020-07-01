#include <stdio.h>
#include "e_array.h"


int main()
{
    int arr[SIZE_ARRAY]={3,2,2,4,2,2} , size;
    
    size = sizeof(arr) / sizeof(arr[0]);
    
    Array_Average(arr , size);
    
    Array_Value_Most(arr , size);

    Array_Even_Odd(arr , size);

    
    return OK;
}

/* Name: Amit Pinhas */
