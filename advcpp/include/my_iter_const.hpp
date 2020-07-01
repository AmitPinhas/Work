#ifndef MY_ITER_CONST_H
#define MY_ITER_CONST_H

#include <vector>

#include "bucket.hpp"
#include "my_pair.hpp"

namespace advcpp
{

template <typename Key, typename Value>
class MyIterConst
{
public:
	typedef typename Bucket<Key, Value>::const_iterator BucketIterator;
	typedef typename std::vector<typename Bucket<Key, Value>::Bucket>::const_iterator VectorIterator;

	MyIterConst(BucketIterator a_iterator, VectorIterator a_currVec, VectorIterator a_end);
	
	MyPair<Key, Value>& operator *();
	
	MyIterConst<Key, Value> operator++();
private:
	BucketIterator FindFirst(BucketIterator a_iterator);
	
private:
	BucketIterator m_iterator;
	VectorIterator m_currVec;
	VectorIterator m_end;
};

template <typename Key, typename Value>
MyIterConst<Key, Value>::MyIterConst(BucketIterator a_iterator, VectorIterator a_currVec, VectorIterator a_end)
: m_iterator(FindFirst(a_iterator))
, m_currVec(a_currVec)
, m_end(a_end)
{
}

template <typename Key, typename Value>
MyPair<Key, Value>& MyIterConst<Key, Value>::operator *()
{
	return *m_iterator;
}

template <typename Key, typename Value>
MyIterConst<Key, Value> MyIterConst<Key, Value>::operator++()
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
typename MyIterConst<Key, Value>::BucketIterator
MyIterConst<Key, Value>::FindFirst(BucketIterator a_iterator)
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

#endif // MY_ITER_CONST_H
