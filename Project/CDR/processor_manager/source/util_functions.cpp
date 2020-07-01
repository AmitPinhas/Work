#include "util_functions.hpp"
#include <cmath> //sqrt
#include <vector>
namespace numbers
{

static bool CheckIfPrime(size_t a_num);
size_t FindNextPrime(size_t a_num);
static size_t FindNextPrimeSearch(size_t a_num);

struct LookUpTable
{
        LookUpTable();
        size_t LookUpPrime(size_t a_num) const;

        const static size_t s_limit = 10000;
        std::vector<unsigned int> m_lookUp;
};

LookUpTable::LookUpTable()
: m_lookUp(s_limit)
{
        for(size_t i = 1 ,prime = 1; i < s_limit; ++i)
        {
                prime = FindNextPrimeSearch(prime);
                m_lookUp[i] = prime;
        }
}

size_t LookUpTable::LookUpPrime(size_t a_num) const
{

	int left=0, right = s_limit - 1;
	int middle;
	while (left <= right)
	{
        middle = left + (right - left) / 2;
		if (m_lookUp[middle] >= a_num)
		{
		    return m_lookUp[middle];
		}
		else
		{
		    right = middle - 1;
		}
    }

    	return m_lookUp[middle];
}



static size_t FindNextPrimeSearch(size_t a_num)
{
    size_t i = a_num + 1;
	/*next prime number after num is before 2*num for n>3*/
	for(size_t bertrandPostulate = 2 * a_num; i < bertrandPostulate ; ++i)
	{
		int isPrime = CheckIfPrime(i);
		if(true == isPrime)
		{
			break;
		}
	}

	return i;
}

size_t FindNextPrime(size_t a_num)
{
	const static size_t s_size = 999;
	static LookUpTable table;
	if(a_num > table.m_lookUp[s_size])
	{
		return table.LookUpPrime(a_num);
	}

	size_t i = a_num+1;
	if(a_num < 2)
	{
	        i = 2;
	}
	FindNextPrimeSearch(a_num);
	/*next prime number after num is before 2*num for n>3*/
	for(size_t bertrandPostulate = 2 * a_num; i < bertrandPostulate ; ++i)
	{
		int isPrime = CheckIfPrime(i);
		if(true == isPrime)
		{
			break;
		}
	}

	return i;
}


static bool CheckIfPrime(size_t a_num)
{
        for(size_t i = 2, endOfCheck = sqrt(a_num); i <= endOfCheck; ++i)
        {
	        if(0 == a_num % i)
	        {
		        return false;
	        }
        }

        return true;
}

}



