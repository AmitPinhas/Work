#ifndef SORTED_SEQUANCE_HPP
#define SORTED_SEQUANCE_HPP

#include <cassert>
#include "my_iter.hpp"
#include "my_iter_rev.hpp"
#include "pred.hpp"

template <typename T, typename Comp>
class SortedSequence
{
public:
	typedef MyIter<T> iterator;

	SortedSequence(const Comp & a_comp);
	
	// SortedSequence(const SortedSequence & a_other) = default
	// ~SortedSequence() = default
	// SortedSequence& operator=(const SortedSequence & a_other) = default

	enum Direction{ HEAD, TAIL};

	MyIter<T> Push(const T & a_item, Direction a_hint = HEAD);
	
	T PopHead();
	T PopTail();
	
	size_t Remove(const T & a_item);
	bool Remove(MyIter<T> a_iter, T& a_item);
	
	MyIter<T> Begin();
	MyIter<T> End();
	
	MyIterRev<T> RBegin();
	MyIterRev<T> REnd();
	
	
	size_t Size() const;
	
	template <typename Container, typename Iter>
	friend size_t Merge(Container a_dst, Iter a_begin, Iter a_end);

private:
	MyIter<T> ScanHead(Pred<T, Comp> a_pred);
	MyIter<T> ScanTail(Pred<T, Comp> a_pred);
	MyIter<T> PushHeadFrom(MyIter<T> a_begin, const T& a_item, Pred<T, Comp> a_pred);
	MyIter<T> PushFrom(MyIter<T> a_begin, const T & a_item);	
	void RemoveItem(MyIter<T> & a_cur, size_t & a_count);
	std::list<T> List();

private:
	std::list<T> m_list;
	Comp m_comp;
	size_t m_size;
};

template< typename T >
size_t Distance(const T a_begin,const T a_end, const T a_it);

template <typename Container, typename Iter>
size_t Merge(Container a_dst, Iter a_begin, Iter a_end)
{
	if(a_begin == a_end)
	{
		return 0;
	}
	
	size_t size = 0;
	
	typename Container::iterator newBegin = a_dst.Push(*a_begin);
	++size;
	
	while(++a_begin != a_end)
	{
		newBegin = a_dst.PushFrom(newBegin, *a_begin);
		++size;
	}
	
	return size;
	
}

template <typename T, typename Less>
bool IsSorted(MyIter<T> a_begin, MyIter<T> a_end, Less a_less)
{
	if(!(a_begin != a_end))
	{
		return true;
	}
	MyIter<T> first = a_begin;
	MyIter<T> second = ++a_begin;
	
	while(second != a_end)
	{
		if(a_less(*second,*first))
		{
			return false;
		}
		++second;
		++first;
	}
	return true;
}

template <typename T, typename Comp>
SortedSequence<T, Comp>::SortedSequence(const Comp & a_comp)
: m_comp(a_comp)
, m_size()
{
}

template <typename T, typename Comp>
std::list<T> SortedSequence<T, Comp>::List() 
{
	return m_list;
}

template <typename T, typename Comp>
MyIter<T> SortedSequence<T, Comp>::Push(const T & a_item, Direction a_hint)
{
	MyIter<T> iterPush = Begin();
	
	if (a_hint == HEAD)
	{
		iterPush = ScanHead(Pred<T, Comp>(a_item, m_comp));
	}	
	else
	{
		iterPush = ScanTail(Pred<T, Comp>(a_item, m_comp));
	}
	
	MyIter<T> retIter = m_list.insert(iterPush.Iter(), a_item);
	m_size++;	
	return retIter;
}

template <typename T, typename Comp>
MyIter<T> SortedSequence<T, Comp>::PushFrom(MyIter<T> a_begin, const T & a_item)
{
	return PushHeadFrom(a_begin, a_item, Pred<T, Comp>(a_item, m_comp));	
}

template <typename T, typename Comp>
T SortedSequence<T, Comp>::PopHead()
{
	assert(m_size > 0);
	
	T Data = *Begin();
	m_list.pop_front();
	--m_size;
	return Data;
}

template <typename T, typename Comp>
T SortedSequence<T, Comp>::PopTail()
{
	assert(m_size > 0);

	T Data = *RBegin();
	m_list.pop_back();
	--m_size;	
	return Data;
}

template <typename T, typename Comp>
void SortedSequence<T, Comp>::RemoveItem(MyIter<T> & a_cur, size_t & a_count)
{
	MyIter<T> copy = a_cur;
	++a_cur;
	++a_count;
	m_list.erase(copy.Iter());
	--m_size;	
}

template <typename T, typename Comp>
size_t SortedSequence<T, Comp>::Remove(const T & a_item)
{
	size_t count = 0;
	
	MyIter<T> cur = Begin();
	MyIter<T> end = End();
	
	while(cur != end)
	{
		if ((*cur) == a_item)
		{
			RemoveItem(cur, count);
		}
		else
		{
			++cur;
		}
	}	
	return count;
}

template <typename T, typename Comp>
bool SortedSequence<T, Comp>::Remove(MyIter<T> a_iter, T& a_item)
{
	if(-1 == Distance(Begin(), End(), a_iter))
	{
		return false;
	}
	
	a_item = *a_iter;
	m_list.erase(a_iter.Iter());
	--m_size;
	return true;
}

template <typename T, typename Comp>
MyIter<T> SortedSequence<T, Comp>::ScanHead(Pred<T, Comp> a_pred)
{
	MyIter<T> cur = Begin();
	MyIter<T> end = End();
	
	while(cur != end)
	{
		if(a_pred(*cur))
		{
			break;
		}
		++cur;
	}
		
	return cur;
}

template <typename T, typename Comp>
MyIter<T> SortedSequence<T, Comp>::PushHeadFrom(MyIter<T> a_begin, const T& a_item, Pred<T, Comp> a_pred)
{
	MyIter<T> end = End();	
	while(a_begin != end)
	{
		if(a_pred(*a_begin))
		{
			break;
		}
		++a_begin;
	}
	
	MyIter<T> retIter = m_list.insert(a_begin.Iter(), a_item);
	m_size++;
	
	return retIter;	
}


template <typename T, typename Comp>
MyIter<T> SortedSequence<T, Comp>::ScanTail(Pred<T, Comp> a_pred)
{
	MyIterRev<T> rBegin = RBegin();
	MyIterRev<T> rEnd = REnd();
	
	while(rBegin != rEnd)
	{
		if(!a_pred(*rBegin))
		{
			break;
		}
		++rBegin;
	}	
		
	return rBegin.Base();	
}

template <typename T, typename Comp>
size_t SortedSequence<T, Comp>::Size() const
{
	return m_size;
}

template <typename T, typename Comp>
MyIter<T> SortedSequence<T, Comp>::Begin() 
{
	return m_list.begin();
}

template <typename T, typename Comp>
MyIterRev<T> SortedSequence<T, Comp>::RBegin()
{
	return m_list.rbegin();
}

template <typename T, typename Comp>
MyIter<T> SortedSequence<T, Comp>::End()
{
	return m_list.end();
}

template <typename T, typename Comp>
MyIterRev<T> SortedSequence<T, Comp>::REnd()
{
	return m_list.rend();	
}

template< typename T >
size_t Distance(const T a_begin,const T a_end, const T a_it)
{
	size_t size = 0;
	
	while ( (a_begin + size) != a_it || (a_begin + size) != a_end )
	{
		++size;
	}
	
	if(a_begin == a_end)
	{
		return -1;
	}
	
	return size;
}

#endif //SORTED_SEQUANCE_HPP
