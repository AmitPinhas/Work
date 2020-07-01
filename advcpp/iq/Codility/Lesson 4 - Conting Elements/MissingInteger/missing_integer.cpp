#include <algorithm> // swap

int solution(vector<int> &A) 
{
    const int vectorSize = A.size();
    
    if(1 == vectorSize)
    {
        if(A[0] == 1)
        {
            return 2;
        }
        
        return 1;
    }
    
    int indexNeg = 0;
    int indexPos = 0;
    
    for(; indexPos < vectorSize; ++indexPos)
    {
        if(A[indexPos] <= 0)
        {
            swap(A[indexPos], A[indexNeg]);
            ++indexNeg;
        }
    }
    
    if(indexNeg == vectorSize)
    {
        return 1;
    }
    
    const int posVectorSize = vectorSize - indexNeg;
    
    for(int i = 0; i < posVectorSize; ++i)
    {
        const int index = abs(A[indexNeg + i]) - 1;
        
        if(index + indexNeg < vectorSize && A[index + indexNeg] > 0 && abs(A[indexNeg + i]) <= posVectorSize)
        {
            A[index + indexNeg] *= -1;
        }
    }
    
    int i = 1;
    int tmpIndexPos = indexNeg;
    
    for(; i <= posVectorSize; ++i, ++indexNeg)
    {
        if(A[indexNeg] > 0)
        {
            break;
        }
    }
    
    for(; tmpIndexPos < vectorSize; ++tmpIndexPos)
    {
        A[tmpIndexPos] = abs(A[tmpIndexPos]);
    }
    
    return i;
}

int solution2(vector<int> &A) 
{
    const int vectorSize = A.size();
    
    if(1 == vectorSize)
    {
        if(1 == A[0])
        {
            return 2;
        }
        return 1;
    }
    
    vector<bool> counter(vectorSize, false);
    
    for(auto element : A)
    {
        if(element > 0 && element <= vectorSize)
        {
            counter[element - 1] = true;
        }
    }
    
    int i = 0;
    
    while(i < vectorSize)
    {
        const bool exists = counter[i];
        
        if(!exists)
        {
            return i + 1;
        }
        
        ++i;
    }
    
    return i + 1;
}
