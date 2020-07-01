#ifndef UTILS_HPP
#define UTILS_HPP
#include <cstdlib>

#include <string>
#include <set>


const static size_t MaxNum = 10000;

namespace myMath
{


class Prime
{
public:
	Prime();

	unsigned int GetNext(unsigned int a_num);

private:
	void FillPrimes();
	bool IsPrime(int a_num) ;

private:
	std::set<unsigned int> m_primeTable;
};

inline unsigned int GetNextPrime(unsigned int a_num)
{
	static Prime primeTable;
	return primeTable.GetNext(a_num);
}


inline Prime::Prime()
:	m_primeTable()
{
	FillPrimes();
}

inline void Prime::FillPrimes()
{
	for (unsigned int i = 2; i < MaxNum; ++i)
	{
		if(IsPrime(i))
		{
			m_primeTable.insert(i);
		}
	}
}

inline bool Prime::IsPrime(int a_num)  
{  
    if (a_num <= 1)  return false;  
    if (a_num <= 3)  return true;  

    if (a_num % 2 == 0 || a_num % 3 == 0) return false;  
    
    for (int i = 5; i * i <= a_num; i = i + 6)  
        if (a_num % i == 0 || a_num % ( i + 2 ) == 0)  
           return false;  
    
    return true;  
}  



inline unsigned int Prime::GetNext(unsigned int a_num)
{
	for (unsigned int i = a_num; true; ++i)
	{
		if (m_primeTable.find(i) != m_primeTable.end() )
		{
			return i;
		}
		
	}
}



}//end myMath namespace

#endif // UTILS_HPP
