#include "mu_test.h"

#include <vector>
#include <set>
#include <cmath> // sqrt

using namespace std;

void splitToPrimes(set<int>& a_primes, int a_num);
bool isPrime(int a_num);
int gcd(int a_first, int a_second);

int solution(vector<int> &A, vector<int> &B) 
{
    int sameSetOfPrimeDivisors = 0;
    const size_t vectorSize = A.size();
    
    for(size_t i = 0; i < vectorSize; ++i)
    {
        int small = A[i];
        int big = B[i];
    
        if(big % small != 0)
        {
            continue;
        }
        
        int firstDiv = big / small;
        
        set<int> smallDivPrimes;
        
        splitToPrimes(smallDivPrimes, small);
        
        set<int> bigDivPrimes;
        
        splitToPrimes(bigDivPrimes, firstDiv);
        
        int counter = 1;
        
        for(auto num: bigDivPrimes)
        {
            if(smallDivPrimes.find(num) == smallDivPrimes.end())
            {
                counter = 0;
                break;
            }
        }

        sameSetOfPrimeDivisors += counter;
    }
    
    return sameSetOfPrimeDivisors;
}

void splitToPrimes(set<int>& a_primes, int a_num)
{
    if(1 == a_num)
    {
        return;
    }

    if(isPrime(a_num))
    {
        a_primes.insert(a_num);
        return;
    }
    
    int firstDiv = sqrt(a_num);
    if(a_num == firstDiv)
    {
        --firstDiv;
    }
    
    while(firstDiv > 2 && a_num % firstDiv)
    {
        --firstDiv;
    }
    
    int secondDiv = a_num / firstDiv;
    
    if(isPrime(firstDiv))
    {
        a_primes.insert(firstDiv);
    }
    else
    {
        splitToPrimes(a_primes, firstDiv);
    }
    
    if(isPrime(secondDiv))
    {
        a_primes.insert(secondDiv);
    }
    else
    {
        splitToPrimes(a_primes, secondDiv);
    }    
}

bool isPrime(int a_num)
{
    if(a_num < 2)
    {
        return false;
    }
    
    int firstDiv = sqrt(a_num);
    if(a_num == firstDiv)
    {
        --firstDiv;
    }
    
    while(firstDiv > 1 && a_num % firstDiv)
    {
        --firstDiv;
    }    
    
    if(firstDiv > 1)
    {
        return false;
    }
    
    return true;
}

int gcd(int a_first, int a_second)
{
    if(a_first % a_second == 0)
    {
        return a_second;
    }
    
    return gcd(a_second, a_first % a_second);
}


UNIT(smoke)

    vector<int> A = {15, 10, 9};
    vector<int> B = {75, 30, 5};

    cout << solution(A,B) << endl;

    ASSERT_PASS();

END_UNIT

TEST_SUITE(common_prime_divisors)

    TEST(smoke)

END_SUITE    