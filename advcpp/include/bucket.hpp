#ifndef BUCKET_HPP
#define BUCKET_HPP

#include <list>
#include <algorithm> // std::find_if
#include "pred_key_is_equal.hpp"
#include "my_pair.hpp"

namespace advcpp
{

template <typename Key, typename Value>
class Bucket
{
public:
	typedef typename std::list<MyPair<Key, Value> >::iterator iterator;
	typedef typename std::list<MyPair<Key, Value> >::const_iterator const_iterator;
	
	void PushFront(const MyPair<Key, Value>& a_pair);	
	
	iterator Begin();
	const_iterator Begin() const;
	
	iterator End();
	const_iterator End() const;	
	
	const_iterator Find(const Key& a_key, size_t a_hashValue) const;
	iterator Find(const Key& a_key, size_t a_hashValue);	
	
	void Remove(const Key& a_key, size_t a_hashValue);
	
	void Clear();

private:
	std::list<MyPair<Key, Value> >& MyBucket();
	const std::list<MyPair<Key, Value> >& MyBucket() const;
	
private:
	std::list<MyPair<Key, Value> > m_bucket;	
};

///////////////////////////////////////////////////////////////////////

template <typename Key, typename Value>
std::list<MyPair<Key, Value> >& 
Bucket<Key, Value>::MyBucket()
{
	return m_bucket;
}

template <typename Key, typename Value>
const std::list<MyPair<Key, Value> >& 
Bucket<Key, Value>::MyBucket() const
{
	return m_bucket;	
}

template <typename Key, typename Value>
void Bucket<Key, Value>::PushFront(const MyPair<Key, Value>& a_pair)
{
	MyBucket().push_front(a_pair);
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator Bucket<Key, Value>::Begin()
{
	return MyBucket().begin();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::const_iterator 
Bucket<Key, Value>::Begin() const
{
	return MyBucket().begin();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator Bucket<Key, Value>::End()
{
	return MyBucket().end();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::const_iterator 
Bucket<Key, Value>::End() const
{
	return MyBucket().end();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::const_iterator 
Bucket<Key, Value>::Find(const Key& a_key, size_t a_hashValue) const
{
	PairKeyIsEqual<Key, Value> pred(a_key, a_hashValue);
	
	return find_if(Begin(), End(), pred);
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator 
Bucket<Key, Value>::Find(const Key& a_key, size_t a_hashValue)
{
	PairKeyIsEqual<Key, Value> pred(a_key, a_hashValue);
	
	return find_if(Begin(), End(), pred);
}

template <typename Key, typename Value>
void Bucket<Key, Value>::Remove(const Key& a_key, size_t a_hashValue)
{
	PairKeyIsEqual<Key, Value> pred(a_key, a_hashValue);
	
	return MyBucket().remove_if(pred);	
}

template <typename Key, typename Value>
void Bucket<Key, Value>::Clear()
{
	MyBucket().clear();
}

}

#endif // BUCKET_HPP
