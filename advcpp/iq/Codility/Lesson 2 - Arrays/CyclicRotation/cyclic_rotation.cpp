#include "mu_test.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> &A, int K)
{
    const size_t vectorSize = A.size();
    
    if(0 == vectorSize)
    {
        return A;
    }
    
    K %= vectorSize;
    
    if(0 == K)
    {
        return A;
    }
    
    vector<int> result(vectorSize, 0);
    
    for(size_t i = 0; i < vectorSize; ++i)
    {
        size_t newIndex = (i + K) % vectorSize;
        result[newIndex] = A[i];
    }
    
    return result;
}


vector<int> solution2(vector<int> &A, int K) 
{
    const size_t vectorSize = A.size();
    
    if(A.empty() || 1 == vectorSize)
    {
        return A;
    }
    
    K %= vectorSize;
    
    if(0 == K)
    {
        return A;
    }
    
    int lastElement = vectorSize - 1;
    
    int newLastElement = vectorSize - 1 - K;
    
    int tmpNewLastElement = vectorSize - 1 - K;

    while (lastElement != newLastElement)
    {
        swap (A[lastElement], A[newLastElement]);
        
        --lastElement;
        --newLastElement;
        
        if(newLastElement < 0)
        {
            newLastElement = tmpNewLastElement;
        }    
        else if(lastElement == tmpNewLastElement)
        {
            tmpNewLastElement = newLastElement;
        }
      }
    
    return A;
}




UNIT(smoke)
    vector<int> v{-1, -2, -3, -4, -5, -6};

    solution2(v, 10);

    for(auto element : v)
    {
        cout << element << " ";
    }
    cout << endl;

END_UNIT


TEST_SUITE(cyclic_rotation)

    TEST(smoke)

END_SUITE

