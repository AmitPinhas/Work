#ifndef MY_ITER_H
#define MY_ITER_H

#include <vector>

#include "bucket.hpp"
#include "my_pair.hpp"

namespace advcpp
{

template <typename Key, typename Value>
class MyIter
{
public:
	typedef typename Bucket<Key, Value>::iterator BucketIterator;
	typedef typename std::vector<typename Bucket<Key, Value>::Bucket>::iterator VectorIterator;

	MyIter(BucketIterator a_iterator, VectorIterator a_currVec, VectorIterator a_end);
	
	MyPair<Key, Value>& operator *();
	
	MyIter<Key, Value> operator++();
private:
	BucketIterator FindFirst(BucketIterator a_iterator);
	
private:
	BucketIterator m_iterator;
	VectorIterator m_currVec;
	VectorIterator m_end;
};

template <typename Key, typename Value>
MyIter<Key, Value>::MyIter(BucketIterator a_iterator, VectorIterator a_currVec, VectorIterator a_end)
: m_iterator(FindFirst(a_iterator))
, m_currVec(a_currVec)
, m_end(a_end)
{
}

template <typename Key, typename Value>
MyPair<Key, Value>& MyIter<Key, Value>::operator *()
{
	return *m_iterator;
}

template <typename Key, typename Value>
MyIter<Key, Value> MyIter<Key, Value>::operator++()
{
	++m_iterator;
	while(m_iterator == (*m_currVec).End())
	{
		++m_currVec;
		if(m_currVec == m_end)
		{
			break;
		}
		m_iterator = (*m_currVec).Begin();		
	}
	return m_iterator;
}

template <typename Key, typename Value>
typename MyIter<Key, Value>::BucketIterator
MyIter<Key, Value>::FindFirst(BucketIterator a_iterator)
{
	while(a_iterator == (*m_currVec).End())
	{
		++m_currVec;
		if(m_currVec == m_end)
		{
			break;
		}
		a_iterator = (*m_currVec).Begin();		
	}
	return a_iterator;	
}

}

#endif // MY_ITER_H
