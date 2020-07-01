#include "mu_test.h"

#include <vector>
#include <cmath> // abs

using namespace std;

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    
    int firstSum = A[0];
    int secondSum = 0;
    
    for(size_t i = 1; i < vectorSize; ++i)
    {
        secondSum += A[i];
    }
    
    size_t minimalDifference = abs(firstSum - secondSum);
    
    for(size_t i = 2; i < vectorSize; ++i)
    {
        firstSum += A[i - 1];
        secondSum -= A[i - 1];
        
        const size_t tmpMinimal = abs(firstSum - secondSum);
        
        if(minimalDifference > tmpMinimal)
        {
            if(0 == tmpMinimal)
            {
                return tmpMinimal;
            }
            
            minimalDifference = tmpMinimal;
        }
    }
    
    return minimalDifference;
}


UNIT(smoke)

    vector<int> v{3, 1, 2, 4, 3};

    ASSERT_THAT(solution(v) == 1);

END_UNIT

TEST_SUITE(tape)

    TEST(smoke)

END_SUITE    