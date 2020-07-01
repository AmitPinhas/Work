#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef> // size_t

namespace advcpp
{

template <typename T>
void Swap(const T& a_first, const T& a_second)
{
	T tmp = a_first;
	a_first = a_second;
	a_second = tmp;
}

namespace numbers
{

size_t NextPrimeLookup(size_t a_capacity);

}

}
#endif /* UTILS_HPP */
