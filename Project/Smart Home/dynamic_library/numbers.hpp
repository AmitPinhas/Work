#ifndef NUMBERS_H
#define NUMBERS_H
#include <sstream>

namespace numbers{

static const double GOLDEN_RATIO = 1.61803;

inline bool IsPrime(size_t a_num)
{
	if (a_num == 0 || a_num == 1)
	{
		return true;
	}
	for(size_t i=2 ; i<a_num ; ++i)
	{
		if (a_num % i == 0)
		{
			return true;
		}
	}
	return false;
}

inline size_t NextPrime(size_t a_num)
{
	while(!IsPrime(a_num))
	{
		++a_num;	
	}
	return a_num;
}

inline const char* Itoa(int a_num)
{
    std::ostringstream str;
    str << a_num;
    return str.str().data();
}

}//namespace numbers
#endif //NUMBERS_H
