#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc, abs() */

#define FINISH 1
#define CONTINUE 0

void SquareArray(int a_array[], size_t a_sizeArray);
void PrintArray(const int a_array[], size_t a_sizeArray);
static void CopyArray(const int a_sourceArray[],  int a_destinationArray[], size_t a_sizeArray);
static int CheckParam(int a_array[], size_t a_sizeArray);

int main()
{
    int testArray[] = {-10, -4, -2, -1, 0, 5, 6, 8};
    int allNegArray[] = {-10, -9, -8, -7, -4, -3, -2, -1};
    int allPosArray[] = {2, 5 ,7, 8, 10};
    int SameValue[] = {-2, -2, -2, -2, -2};

    const size_t sizeArray = sizeof(testArray) / sizeof(testArray[0]);
    const size_t sizeNegArray = sizeof(allNegArray) / sizeof(allNegArray[0]);
    const size_t sizePosArray = sizeof(allPosArray) / sizeof(allPosArray[0]);
    const size_t sizeSameValue = sizeof(SameValue) / sizeof(SameValue[0]);

    PrintArray(testArray, sizeArray);

    SquareArray(testArray, sizeArray);

    PrintArray(testArray, sizeArray);

    printf("\n");

    PrintArray(allNegArray, sizeNegArray);

    SquareArray(allNegArray, sizeNegArray);

    PrintArray(allNegArray, sizeNegArray);

    printf("\n");

    PrintArray(allPosArray, sizePosArray);

    SquareArray(allPosArray, sizePosArray);

    PrintArray(allPosArray, sizePosArray); 

    printf("\n");

    PrintArray(SameValue, sizeSameValue);

    SquareArray(SameValue, sizeSameValue);

    PrintArray(SameValue, sizeSameValue);           

    return 0;
}

void SquareArray(int a_array[], size_t a_sizeArray)
{
    size_t first = 0;
    size_t last = a_sizeArray - 1;
    size_t indexTmp; 

    int *tmpArray;

    if (FINISH == CheckParam(a_array, a_sizeArray))
    {
        return;
    }

    tmpArray = (int*)malloc(a_sizeArray * sizeof(int));

    if(NULL == tmpArray)
    {
        return;
    }    

    for(last = a_sizeArray - 1, indexTmp = a_sizeArray - 1; first != last && indexTmp > 0; --indexTmp)
    {
        if(abs(a_array[first]) > abs(a_array[last]))
        {
            tmpArray[indexTmp] = a_array[first] * a_array[first];
            ++first;
        }
        else
        {
            tmpArray[indexTmp] = a_array[last] * a_array[last];
            --last;            
        }
    }

    tmpArray[0] = a_array[first] * a_array[first];

    CopyArray(tmpArray,  a_array, a_sizeArray);

    free(tmpArray);

    return;
}

void PrintArray(const int a_array[], size_t a_sizeArray)
{
    size_t i;

    for(i = 0; i < a_sizeArray; ++i)
    {
        printf("%d ", a_array[i]);
    }   

    printf("\n"); 

    return;
}

void CopyArray(const int a_sourceArray[],  int a_destinationArray[], size_t a_sizeArray)
{
    size_t i;

    for(i = 0; i < a_sizeArray; ++i)
    {
        a_destinationArray[i] = a_sourceArray[i];
    }    

    return;
}

int CheckParam(int a_array[], size_t a_sizeArray)
{
    if(NULL == a_array || 0 == a_sizeArray)
    {
        return FINISH;
    }

    if(1 == a_sizeArray)
    {
        *a_array *= *a_array;
        return FINISH;
    }

    return CONTINUE;
}