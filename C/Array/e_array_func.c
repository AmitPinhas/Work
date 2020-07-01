#include <stdio.h>
#include "e_array.h"

double Sum(double result , double num);
int swap(int *a , int *b);
int Check_Array(int _arr[] , int _size);
int Print_Array(int _arr[] , int _size);
int Check_If_Swap(int *value1 , int *value2 , int *change);


int Array_Even_Odd(int _arr[] , int _size)
{
	int index1 , index2 , change , size_tmp , result;
	
	if((result=Check_Array(_arr,_size)) != OK)
	{
	    return result;
	}
	
	
   for(change=1 , size_tmp=_size ; change ; change=0 , size_tmp--)
    {
	for(index1=0 ,index2=1 ; index2<size_tmp ; index1++ , index2++ )
	{
	    Check_If_Swap(&_arr[index1] , &_arr[index2] , &change);

	}
	}
	
	Print_Array(_arr , _size); 
	
	return OK;
	
}

int Array_Value_Most(int _arr[] , int _size)
{
	int count1=0 , countmax=0 , index_max=0 , index , index2 , result;
	
	if((result=Check_Array(_arr,_size)) != OK)
	{
	    return result;
	}
	
	for(index=0 ; index<_size ; index++)
	{
	    for(index2=1 ; index2<_size ; index2++)
	    {
	        if(_arr[index] == _arr[index2])
	        {
	            count1++;
	        }
	        if(count1 > countmax)
	        {
	            countmax=count1;
	            index_max=index;
	        }
	    }
	    count1=0;
	}
	
	printf("the value is %d\n" , _arr[index_max]);
	
	return OK;
}

int Array_Average(int _arr[] , int _size)
{
    int index , result_check;
    double result;
    
    if((result_check=Check_Array(_arr,_size)) != OK)
	{
	    return result_check;
	}
	
    
    for(index=0 , result=0 ; index<_size ; index++)
    {
        result =Sum((double)result ,(double)_arr[index]/_size);
    }
    
    printf("the average is %.2f\n",result);
    
    return OK;
}

double Sum(double result , double num)
{
    result +=num;
    
    return result;
}

int swap(int *a , int *b)
{
    int tmp;
    
    tmp=*a;
    *a=*b;
    *b=tmp;
    return OK;
}

int Check_Array(int _arr[] , int _size)
{
    if(_arr == NULL && _size<1)
    {
        return ERROR_SIZE_POINTER;
    }
    else if(_arr == NULL)
    {
        return ERROR_POINTER;
    }
    else if(_size<1)
    {
        return ERROR_SIZE;
    }
    
    return OK;
}

int Print_Array(int _arr[] , int _size)
{
    int index;
    
    for(index=0 ; index<_size ; index++)
    {
        printf("%d ", _arr[index]);
    }
    putchar('\n');
}

int Check_If_Swap(int *value1 , int *value2 , int *change)
{
     if ((*value1%2==1) && (*value2%2==0))
	        {
	           swap(value1 , value2);
	           *change=1;
	        }
	        
	        return OK;
}


