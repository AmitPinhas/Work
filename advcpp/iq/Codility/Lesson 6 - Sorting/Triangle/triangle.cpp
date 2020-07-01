// https://app.codility.com/demo/results/trainingFQ5PTC-3PJ/



#include <algorithm> // sort

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    
    if(vectorSize < 3)
    {
        return 0;
    }
    
    sort(A.begin(), A.end());
    
    for(size_t i = 2; i < vectorSize; ++i)
    {
        const int first = A[i - 2];
        const int second = A[i - 1];
        const int third = A[i];
        
        if((first > third - second) &&
           (first > second - third) &&
           (second > first - third))
        {
            return 1;   
        }
    }
    
    return 0;
}


// https://app.codility.com/demo/results/trainingM6U4MJ-8UF/

int solution2(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    
    if(vectorSize < 3)
    {
        return 0;
    }
    
    sort(A.begin(), A.end());
    
    for(size_t i = 2; i < vectorSize; ++i)
    {
        const int first = A[i - 2];
        const int second = A[i - 1];
        const int third = A[i];
        
        if(second > third - first)
        {
            return 1;   
        }
    }
    
    return 0;
}