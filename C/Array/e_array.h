#define OK 1
#define SIZE_ARRAY 6
#define ERROR_SIZE_POINTER -1
#define ERROR_POINTER -2
#define ERROR_SIZE -3


/*
Description: average calculation
Input: array of integer number and size of array
Output: OK / ERROR_SIZE_POINTER / ERROR_POINTER / ERROR_SIZE
Error: OK - result average  
       ERROR_SIZE_POINTER- size<1 && arr==NULL
       ERROR_POINTER- arr==NULL
       ERROR_SIZE- size<1

*/
int Array_Average(int _arr[] , int _size);


/*
Description: returns the value that occur the most in this array
Input: array of integer number and size of array
Output: OK / ERROR_SIZE_POINTER / ERROR_POINTER / ERROR_SIZE
Error: OK - result Value  
       ERROR_SIZE_POINTER- size<1 && arr==NULL
       ERROR_POINTER- arr==NULL
       ERROR_SIZE-
*/
int Array_Value_Most(int _arr[] , int _size);


/*
Description: first will be all even numbers and after that all odd numbers
Input: array of integer number and size of array
Output: OK / ERROR_SIZE_POINTER / ERROR_POINTER / ERROR_SIZE
Error: OK - return the new array
       ERROR_SIZE_POINTER- size<1 && arr==NULL
       ERROR_POINTER- arr==NULL
       ERROR_SIZE-
*/
int Array_Even_Odd(int _arr[] , int _size);

