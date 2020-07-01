#include <stdio.h>

typedef enum { FOUND, NOT_FOUND, ERROR } Status;

Status Exist(int a_array[], size_t a_sizeArray, int a_num, int *a_indexNum);

int main()
{
    int arr[] = {1,2,3,4,5,75,765,654};
    Status status;
    int index;
    size_t sizeArr = sizeof(arr) / sizeof(arr[0]);
    int numToFind = 75;
    int numNotFound = 755;

    status = Exist(arr, sizeArr, numToFind, &index);

    if(status == FOUND)
    {
        puts("Pass");
    }

    status = Exist(arr, sizeArr, numNotFound, &index);

    if(status == NOT_FOUND)
    {
        puts("Pass");
    }  
    
    status = Exist(NULL, sizeArr, numNotFound, &index);

    if(status == ERROR)
    {
        puts("Pass");
    }  

    status = Exist(arr, sizeArr, numNotFound, NULL);

    if(status == ERROR)
    {
        puts("Pass");
    }         

    return 0;
}

Status Exist(int a_array[], size_t a_sizeArray, int a_num, int *a_indexNum)
{
    size_t indexLast = a_sizeArray - 1;
    size_t index = 0;

    if(a_array == NULL || a_indexNum == NULL)
    {
        return ERROR;
    }

    if(a_array[indexLast] == a_num)
    {
        *a_indexNum = indexLast;
        return FOUND;
    }

    a_array[indexLast] = a_num;

    while(a_array[index] != a_num)
    {
        ++index;
    }

    if(index == indexLast)
    {
        return NOT_FOUND;
    }
    else
    {
        *a_indexNum = index;
        return FOUND;
    }
    
}