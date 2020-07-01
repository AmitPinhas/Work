// https://app.codility.com/demo/results/trainingGF3572-V6Y/  100%

#include "mu_test.h"

#include <cmath> // sqrt
#include <vector>

using namespace std;

void FillPrimes(vector<bool> &a_primes, size_t a_maxLimit);

vector<int> solution(int N, vector<int> &P, vector<int> &Q) 
{
    const size_t maxLimit = N / 2;
    vector<bool> primes;
    
    FillPrimes(primes, maxLimit);
    
    const size_t sizeP = P.size();
    
    vector<int> result(sizeP);
    
    for(size_t j = 0; j < sizeP; ++j)
    {
        int counter = 0;
        const int small = P[j] - 1;
        const int big = Q[j];
        
        size_t firstDiv = sqrt(small);        
        int factorial = 0;        
        
        size_t i = 0;
        
        for(; primes[i] <= firstDiv; ++i)
        {
            ++factorial;
            factorial *= factorial;
        }
        
        counter -= factorial;
        
        size_t secondDiv = small / 2;
        size_t maxLimit = i;
        
        for(; primes[i] <= secondDiv; ++i)
        {
            for(size_t j = 0; i < maxLimit; ++j)
            {
                if(primes[i] * primes[j] <= small)
                {
                    --counter;
                }
            }
        }
        
        firstDiv = sqrt(big);  
        factorial = 0;  
        i = 0;
        
        for(; primes[i] <= firstDiv; ++i)
        {
            ++factorial;
            factorial *= factorial;
        }
        
        counter += factorial;        
        
        secondDiv = big / 2;
        
        maxLimit = i;

        for(; primes[i] <= secondDiv; ++i)
        {
            for(size_t k = 0; k < maxLimit; ++k)
            {
                if(primes[i] * primes[k] <= big)
                {
                    ++counter;
                }
            }
        }
        
        result[j] = counter;
    }
    
    return result;
}

void FillPrimes(vector<bool> &a_primes, size_t a_maxLimit)
{
    for(size_t num = 2; num <= a_maxLimit; ++num)
    {
        size_t firstDiv = sqrt(num); 
        bool isPrime = true;
        
        if(firstDiv == num)
        {
            --firstDiv;
        }
        while(firstDiv > 1 && isPrime)
        {
            if(num % firstDiv == 0)
            {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
        {
            a_primes.push_back(num);
        }
    }
    
    return;
}


UNIT(smoke)

    vector<int> p{1, 4, 16};
    vector<int> q{26, 10, 20};   
    vector<int> result =  solution(26, p, q);

    ASSERT_EQUAL(result[0], 10);
    ASSERT_EQUAL(result[1], 4);
    ASSERT_EQUAL(result[2], 0);        

END_UNIT

TEST_SUITE(count_semiprimes)

    TEST(smoke)

END_SUITE    


