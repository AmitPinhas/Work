

#include <cmath> // abs

int solution(int X, vector<int> &A) 
{
    for(size_t i = 0; i < A.size(); ++i)
    {
        size_t index = abs(A[i]) - 1;
        
        if(A[index] > 0)
        {
            --X;
            
            if(0 == X)
            {
                return i;
            }
            
            A[index] *= -1;
        }
    }
    
    return -1;

}

