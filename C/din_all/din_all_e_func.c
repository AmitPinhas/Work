#include <stdio.h>
#include <stdlib.h>
#include "din_all_e.h"
#define MAGIC_NUMBER 28011993

DynamicArrayError CheckIncrementAlloc(DynamicArray *_dynamInArrayPtr);
DynamicArrayError CheckDeleteParams(DynamicArray *_dynamInArrayPtr, int* _data);
DynamicArrayError Param_Check_Creat(int _size ,int _blockSize);

struct DynamicArray{
     int *dArray;
     int dArraySize;
     int dArrayBlock;
     int NumOfElements;
     int magic_num;
};

DynamicArray* DynamicArrayCreat(int _size , int _blockSize)
{
     DynamicArray *ptr_param;
     DynamicArrayError result_check;
     
     if((result_check=Param_Check_Creat(_size , _blockSize)) != OK)
     {
          return NULL;
     }
     
     ptr_param = (DynamicArray*)malloc(sizeof(DynamicArray));
     
     if ( NULL == ptr_param)
     {
          return NULL;
     }
     
     ptr_param->dArray = (int*)malloc((_size) * sizeof(int));
     
     if( NULL == ptr_param->dArray)
     {
          free(ptr_param);
          return NULL;
     } 
     
     ptr_param->dArraySize= _size;
     ptr_param->dArrayBlock= _blockSize;
     ptr_param->NumOfElements=0;
     ptr_param->magic_num =MAGIC_NUMBER;
     
     return ptr_param;

}

void DynamicArrayDestroy(DynamicArray *_dynamInArrayPtr)
{
     if(_dynamInArrayPtr != NULL && _dynamInArrayPtr->magic_num == MAGIC_NUMBER)
     {          
       _dynamInArrayPtr->magic_num =0;   
       if(_dynamInArrayPtr->dArray != NULL )
       {
         free(_dynamInArrayPtr->dArray);
       }
       
       free(_dynamInArrayPtr);
     }
}

DynamicArrayError DynamicArrayInsert(DynamicArray *_dynamInArrayPtr, int _data)
{
     int *ptr_tmp ;
     DynamicArrayError result_check;
     
     if( NULL == _dynamInArrayPtr)
     {
          return PTR_ERROR;
     }
     
     if((result_check = CheckIncrementAlloc(_dynamInArrayPtr)) != OK)
     {
          return result_check;
     }
     
     _dynamInArrayPtr->dArray[_dynamInArrayPtr->NumOfElements] = _data;
     _dynamInArrayPtr->NumOfElements +=1;
     
     return OK;
}

DynamicArrayError DynamicArrayDelete(DynamicArray *_dynamInArrayPtr, int *_data)
{
   DynamicArrayError result;
   
     if((result = CheckDeleteParams(_dynamInArrayPtr,  _data)) != OK)
     {
          return result;
     }
    
      *_data = _dynamInArrayPtr->dArray[_dynamInArrayPtr->NumOfElements-1];
      
      _dynamInArrayPtr->NumOfElements -=1;
      
      return OK;
}


DynamicArrayError CheckIncrementAlloc(DynamicArray *_dynamInArrayPtr)
{
     int *tmp;
     
     if(_dynamInArrayPtr->NumOfElements == _dynamInArrayPtr->dArraySize)
     {
          if (0 == _dynamInArrayPtr->dArrayBlock)
          {
               return ERROR_OVERFLOW;
          }
          
          if((tmp=(int*)realloc(_dynamInArrayPtr->dArray , sizeof(int)*((_dynamInArrayPtr->dArraySize)+_dynamInArrayPtr->dArrayBlock))) == NULL)
          {
               return REALLOC_FAILED;
          } 
          
          _dynamInArrayPtr->dArraySize +=_dynamInArrayPtr->dArrayBlock;
          _dynamInArrayPtr->dArray=tmp;
     }
     
     return OK;
}

DynamicArrayError CheckDeleteParams(DynamicArray *_dynamInArrayPtr, int* _data)
{
     if( NULL == _dynamInArrayPtr || NULL == _data )
     {
          return PTR_ERROR;
     }
     
     if( _dynamInArrayPtr->NumOfElements <=0)
     {
          return ERROR_NO_ELEMNTS;
     }
     
     return OK;
}

DynamicArrayError Param_Check_Creat(int _size ,int _blockSize)
{
     if(_size<0 || _blockSize<0)
     {
          return ERROR_PARAMS;
     }
     
     if(_size==0 && _blockSize ==0)
     {
          return ERROR_PARAMS;
     }
     
     return OK;
}


