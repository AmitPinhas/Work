#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstddef>
#include <string>
namespace cpp
{


void UtilClearStringFromSpaces(std::string &a_str); 
template <typename T>
void Swap(T &a_num1, T &a_num2);
template <typename T>
void CopyArr(T* a_dest, const T* a_src, size_t a_len);
template <typename IteratorType, typename Predicate>
bool IsSorted(IteratorType a_begin, IteratorType a_end, Predicate a_less);

template <typename Cont, typename IterType>
size_t Merge(Cont& a_sequence, IterType a_begin, IterType a_end);
////////////////////////////////////////////////////////////////////////////

template <typename T>
void Swap(T &a_num1, T &a_num2)
{
	T temp = a_num1;
	a_num1 = a_num2;
	a_num2 = temp;
}

template <typename T>
void CopyArr(T* a_dest, const T* a_src, size_t a_len)
{
	for(size_t i = 0; i < a_len;i++)
	{
		a_dest[i] = a_src[i];
	}
}

template <typename IteratorType, typename Predicate>
bool IsSorted(IteratorType a_begin, IteratorType a_end, Predicate a_less)
{
	if(a_begin == a_end)
	{
		return true;
	}
	
	IteratorType next = a_begin;
	while(++next != a_end)
	{
		if(a_less(*next, *a_begin))
		{
			return false;
		}
		++a_begin;
	}
	
	return true;		
}

template <typename Cont,typename IterType>
size_t Merge(Cont& a_sequence, IterType a_begin, IterType a_end)
{
	size_t numOfItems = 0;
	typename Cont::iterator toPushFrom = a_sequence.Begin();
	while(a_begin != a_end)
	{
		toPushFrom = a_sequence.Push(*a_begin, toPushFrom);
		++numOfItems;
		++a_begin;
	}
	
	return numOfItems;
}

// Comparator assumes that copy constructor exists and functional
template <typename T,typename Compare>
struct Comparator{
public:
	Comparator(const T& a_value, const Compare& a_cmp);
	bool operator()(const T& a_elem) const;
	
	const T& m_value;	
	const Compare m_cmp;
};

template <typename T,typename Compare>
Comparator<T, Compare>::Comparator(const T& a_value, const Compare& a_cmp)
: m_value(a_value)
, m_cmp(a_cmp)
{
}

template <typename T,typename Compare>
bool Comparator<T, Compare>::operator()(const T& a_elem) const
{
	return !m_cmp(a_elem, m_value);
}

// Comparator assumes that copy constructor exists and functional
template <typename T,typename Compare>
struct OpositeComparator{
public:
	OpositeComparator(const T& a_value, const Compare& a_cmp);
	bool operator()(const T& a_elem) const;
	
	const T& m_value;	
	const Compare m_cmp;
};

template <typename T,typename Compare>
OpositeComparator<T, Compare>::OpositeComparator(const T& a_value, const Compare& a_cmp)
: m_value(a_value)
, m_cmp(a_cmp)
{
}

template <typename T,typename Compare>
bool OpositeComparator<T, Compare>::operator()(const T& a_elem) const
{
	return m_cmp(a_elem, m_value);
}

}






#endif /*UTIL_HPP*/
