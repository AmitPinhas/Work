
enum DynamicArrayError {OK , ERROR_NO_ELEMNTS , PTR_ERROR  , ERROR_OVERFLOW , REALLOC_FAILED , ERROR_PARAMS } ;

typedef enum DynamicArrayError DynamicArrayError ;

typedef struct DynamicArray DynamicArray ;

/*
    Description: Makes pointer to the structure of the parameters through dynamic allocation And then reboots into variables,
                 including another dynamic allocation to a pointer that is inside the structure.
    Input: size of the array and inc_array_block.
    Output: OK / NULL .
    ERROR: OK - Returns a pointer to a new array .
           NULL - return null pointer , if size<0 or inc<0 or size and inc = 0 , or dinamic allocation failed .
    Note: if dinamic allocation to the structure succeeded and dinamic allocation to tha array failed , the func free the dinamic allocation to the structure.
*/
DynamicArray* DynamicArrayCreat(int _size , int _blockSize);

/*
    Description: free dinamic allocation to the array and free dinamic allocation to the structure.
    Input: pointer from DynamicArray type to the structure of params.
    Output: no output.
    ERROR : no error.
*/
void DynamicArrayDestroy(DynamicArray *_dynamInArrayPtr);

/*
    Description: Insertion of an organ into the array to the last limb and increase it when needed.
    Input: pointer from DynamicArray type to the structure of params and the data that we want add to ta array.
    Output: OK /  PTR_ERROR / ERROR_OVERFLOW / REALLOC_FAILED.
    ERROR: OK - insert successfully , the number of new elements has been updated in the structure , 
                if we increased the array , the size of the new array is updated in the structure and also the new pointer .
           PTR_ERROR -  _dynamInArrayPtr = NULL.
           ERROR_OVERFLOW - if num of element = size and inc = 0 .
           REALLOC_FAILED - Failed to scale array .
*/
DynamicArrayError DynamicArrayInsert(DynamicArray *_dynamInArrayPtr, int _data);

/*
    Description: Deletes the information in the last element of the array and returns it , update num of element.
    Input: pointer from DynamicArray type to the structure of params and the pointer to data that we want remove from the array
    Output: OK / ERROR_NO_ELEMNTS / PTR_ERROR.
    Output details: OK - delete successfully , we returns the data with the pointer that we send , num of element update .
                    ERROR_NO_ELEMNTS - no element to delete , num of element <=0 .
                    PTR_ERROR -  if the pointers _dynamInArrayPtr = NULL or _data = NULL  . 
*/
DynamicArrayError DynamicArrayDelete(DynamicArray *_dynamInArrayPtr, int *_data);
