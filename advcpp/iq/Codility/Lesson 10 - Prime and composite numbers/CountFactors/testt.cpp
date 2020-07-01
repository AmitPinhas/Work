#include "mu_test.h"

#include <cmath> // sqrt

int solution(int N) 
{
    size_t maxLimit = sqrt(N);
    
    int factors = pow(maxLimit, 2) == N ? -1: 0;
    
    for(size_t i = 1; i <= maxLimit; ++i)
    {
        factors += N % i ? 0: 2; 
    }
    
    return factors;
}

UNIT(smoke)

    ASSERT_EQUAL(solution(30), 8);

END_UNIT

TEST_SUITE(count_factors)

    TEST(smoke)

END_SUITE    