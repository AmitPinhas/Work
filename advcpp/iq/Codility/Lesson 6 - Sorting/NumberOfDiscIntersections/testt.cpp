// https://app.codility.com/demo/results/training4WVWBJ-6HR/

#include "mu_test.h"

#include <algorithm> // sort

int solution(vector<int> &A) 
{
    vector<long> openDiscs;
    vector<long> closeDiscs;
    
    for(size_t i = 0; i < A.size(); ++i)
    {
        openDiscs.push_back(i - A[i]);
        closeDiscs.push_back(i + A[i]);        
    }
    
    sort(openDiscs.begin(), openDiscs.end());
    sort(closeDiscs.begin(), closeDiscs.end());
    
    size_t currOpenDiscs = 0;
    size_t intersections = 0;
    
    size_t i = 0;
    size_t j = 0;
    
    while(i < openDiscs.size())
    {
        if(openDiscs[i] <= closeDiscs[j])
        {
            intersections += currOpenDiscs;
            
            if(intersections > 10000000)
            {
                return -1;
            }
            
            ++currOpenDiscs;
            
            ++i;
        }
        else
        {
            --currOpenDiscs;
            ++j;
        }
    }
    
    return intersections;
}



UNIT(test_one)

    ASSERT_PASS();

END_UNIT

TEST_SUITE(test)

    TEST(test_one)

END_SUITE    