// https://app.codility.com/demo/results/training32JFNE-WX3/

#include <cmath> // sqrt

int solution(int N) 
{
   size_t maxDiv = sqrt(N);
    
    while(N % maxDiv != 0)
    {
        --maxDiv;
    }
    
    return 2 * (maxDiv + N / maxDiv);
}

