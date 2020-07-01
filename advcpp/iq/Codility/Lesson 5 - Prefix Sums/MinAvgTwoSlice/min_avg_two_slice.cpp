#include "mu_test.h"

#include <iostream>
#include <vector>

using namespace std;

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    
    int result = 0;

    if(2 == vectorSize)
    {
        return result;
    }
    
    int sum = A[0] + A[1];
    double minAvg = sum / 2.0;
    int tmpResult = 0;
    
    for(size_t i = 2; i < vectorSize; ++i)
    {
        sum += A[i];
        double currAvg = sum / double(i - tmpResult + 1);
        double tmpAvg = (A[i] + A[i - 1]) / 2.0;
        
        if(tmpAvg < currAvg)
        {
            tmpResult = i - 1;
            sum = A[i] + A[i - 1];
        }
        if(tmpAvg < minAvg)
        {
            result = tmpResult;
            minAvg = tmpAvg;
        }
        if(currAvg < minAvg)
        {
            result = tmpResult;
            minAvg = currAvg;
        }
    }
    
    return result;
}

UNIT(smoke)
    vector<int> v{-3, -5, -8, -4, -10};

    cout << solution(v) << endl;

    ASSERT_PASS();

END_UNIT


TEST_SUITE(cyclic_rotation)

    TEST(smoke)

END_SUITE