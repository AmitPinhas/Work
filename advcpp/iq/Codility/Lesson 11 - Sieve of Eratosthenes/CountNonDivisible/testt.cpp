// https://app.codility.com/demo/results/trainingSWGQ2K-FPH/

#include <cmath> // sqrt

vector<int> solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    
    if(1 == vectorSize)
    {
        vector<int> result = {0};
        
        return result;
    }
    
    const size_t counterSize = 2 * vectorSize;
    
    vector<size_t> counterElements(counterSize, 0);
    
    for(auto num: A)
    {
        ++counterElements[num - 1];
    }
    
    vector<int> result(vectorSize, vectorSize);
    
    for(size_t i = 0; i < vectorSize; ++i)
    {
        const int element = A[i];
        int firstDiv = sqrt(element);
        
        while(firstDiv > 0)
        {
            if(element % firstDiv == 0)
            {
                result[i] -= counterElements[firstDiv - 1];
                
                const int secondDiv = element / firstDiv;
                
                if(firstDiv != secondDiv)
                {
                    result[i] -= counterElements[secondDiv - 1];   
                }
            }
            
            --firstDiv;
        }
    }
    
    return result;
}

