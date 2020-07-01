#ifndef ITR_HPP
#define ITR_HPP
#include <iterator>
#include <cstdlib> //size_t, srand, rand
#include "utils.hpp" // swap


template< typename Iter >
bool IsEmpty(Iter a_begin, Iter a_end)
{
	return a_begin == a_end;
}

template< typename Iter, typename Pred  >
bool Exists(Iter a_begin, Iter a_end, Pred a_pred, Iter & a_iterFound)
{
	a_iterFound = a_end;
	
	while ( a_begin != --a_iterFound )
	{
		if( a_pred(*a_iterFound) )
		{
			return true;;
		}
	}	
	
	if ( a_pred(*a_iterFound) )
	{
		return true;
	}	
	
	return false;
}

template< typename Iter, typename Pred  >
Iter FindLast(Iter a_begin, Iter a_end, Pred a_pred)
{
	if(IsEmpty(a_begin, a_end))
	{
		return a_end;
	}
	
	Iter iterFound ;
	
	if(Exists(a_begin,  a_end, a_pred, iterFound))
	{
		return iterFound;
	}			
	
	return a_end;
}

template< typename T >
size_t Distance(const T a_begin,const T a_it)
{
	size_t size = 0;
	
	while ( (a_begin + size) != a_it )
	{
		++size;
	}
	return size;
}

template <typename Iter>
bool Sort (Iter a_begin, Iter a_end)
{
	bool isSort = 1 ;
	Iter left = a_begin;
	Iter right = ++a_begin;
	
	while (left !=  a_end)
	{
		if( *left > *right )
		{
			Swap( *left, *right);
			isSort = 0;
		}
		++left;
		++right;
	}
	return isSort;
}



template <typename Iter>
void BubbleSort (Iter a_begin, Iter a_end)
{
	if(IsEmpty(a_begin, a_end))
	{
		return;
	}
	
	while(a_begin != --a_end)
	{
		if(Sort(a_begin, a_end))
		{
			break;
		}		
	}
	return;
} 

template <typename IterA, typename IterB>
bool CheckParam(IterA a_last, IterA a_end, IterB a_beginB, IterB a_endB)
{
	if (a_last-a_end != a_beginB-a_endB)
	{
		return false;
	}	
	return true;
}

template <typename IterA, typename IterB>
void ConcatenateRest(IterA a_rPos, IterB a_rBeginB, IterB a_rEndB)
{
	while(a_rBeginB != a_rEndB)
	{	
		*a_rPos = *a_rBeginB;
		++a_rBeginB;
		++a_rPos;
	}	
}

template <typename IterA>
void Concatenate(IterA & a_rPos, IterA & a_rBig)
{
	*a_rPos = *a_rBig;
	++a_rBig;	
	++a_rPos;
}

template <typename IterA, typename IterB>
void Merge(IterA a_begin, IterA a_last, IterA a_end, IterB a_beginB, IterB a_endB)
{
	if (CheckParam(a_last, a_end, a_beginB, a_endB) == false)
	{
		return;
	}
	
	std::reverse_iterator<IterA> rEnd(a_begin);
	std::reverse_iterator<IterA> rLast(a_last);	
	std::reverse_iterator<IterA> rPos(a_end);	
	std::reverse_iterator<IterB> rEndB(a_beginB);
	std::reverse_iterator<IterB> rBeginB(a_endB);			

	while(rLast != rEnd && rBeginB != rEndB)
	{
		if(*rLast > *rBeginB)
		{
			Concatenate(rPos, rLast);
		}
		else
		{
			Concatenate(rPos, rBeginB);
		}
	}
		
	ConcatenateRest(rPos, rBeginB, rEndB);
}




template< typename T >
struct Pred
{
	Pred(T const &a_data);
	
	bool operator()(T const& a_data) const;
	
private:
		T m_data;
};

template< typename T >
Pred<T>::Pred(T const &a_data)
: m_data(a_data)
{
}

template< typename T >
bool Pred<T>::operator()(T const& a_data) const
{
	return 	m_data == a_data;
}


#endif /* ITR_HPP */
