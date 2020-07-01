#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>

#include "bucket.hpp"
#include "utils.hpp"
#include "my_pair.hpp"
#include "my_iter.hpp"
#include "my_iter_const.hpp"
#include "mutex.hpp"

namespace advcpp
{

template < typename Key, typename Value, typename HashFunc>
// Key: must have operator == (Equal to) and copy constructor
class HashTable : private std::vector<typename Bucket<Key, Value>::Bucket>
{
public:
	typedef typename Bucket<Key, Value>::iterator iterator;
	typedef typename Bucket<Key, Value>::const_iterator const_iterator;	
	
	HashTable(size_t a_capacity, const HashFunc& a_hashFunc);
	
	// ~HashTable() = default;	
	// HashTable(const HashTable& a_other)  = default;	
	// HashTable& operator=(const HashTable& a_other) = default;
	
	MyIter<Key, Value> Insert(const Key& a_key, const Value& a_value);
	
	MyIterConst<Key, Value> Find(const Key& a_key) const;
	MyIter<Key, Value> Find(const Key& a_key);
	
	bool Remove(const Key& a_key, Value& a_value);
	
	Value& operator[](const Key& a_key);
		
	MyIter<Key, Value> Begin();
	const_iterator Begin() const;
	
	MyIter<Key, Value> End();
	const_iterator End() const;		
	
	size_t Size() const;
	size_t Capacity() const;
	double LoadFactor() const;
	
	void Clear();

	void Resize(size_t a_capacity);
	
	void Swap(HashTable& a_hash);
	
private:
	size_t Index(const Key& a_key) const;
	typename Bucket<Key, Value>::Bucket& GetBucket(size_t a_index);
	
private:
	HashFunc m_hashFunc;
	size_t m_capacity;
	size_t m_size;		
	
};

/////////////////////////////////////////////////////////////////////
template <typename Key, typename Value, typename HashFunc>
void Swap(HashTable<Key, Value, HashFunc>& a_first, HashTable<Key, Value, HashFunc>& a_second);

template <typename Key, typename Value, typename HashFunc>
HashTable<Key, Value, HashFunc>::HashTable(size_t a_capacity, const HashFunc& a_hashFunc)
: std::vector<typename Bucket<Key, Value>::Bucket>(numbers::NextPrimeLookup(a_capacity))
, m_hashFunc(a_hashFunc)
, m_capacity(numbers::NextPrimeLookup(a_capacity))
, m_size()
{
}


template <typename Key, typename Value, typename HashFunc>
MyIter<Key, Value> HashTable<Key, Value, HashFunc>::Begin()
{
	MyIter<Key, Value> iter(this->begin()->Begin(), this->begin(), this->end());
	return iter;
	//return this->begin()->Begin();
}

template <typename Key, typename Value, typename HashFunc>
typename HashTable<Key, Value, HashFunc>::const_iterator 
HashTable<Key, Value, HashFunc>::Begin() const
{
	return Begin();
}

template <typename Key, typename Value, typename HashFunc>
MyIter<Key, Value>
HashTable<Key, Value, HashFunc>::End()
{
	MyIter<Key, Value> iter(this-> at(Capacity()-1).End(), (this-> end()-1), this-> end());
	return iter;
}

template <typename Key, typename Value, typename HashFunc>
typename HashTable<Key, Value, HashFunc>::const_iterator 
HashTable<Key, Value, HashFunc>::End() const
{
	return this-> at(Capacity()-1).End();
}

template < typename Key, typename Value, typename HashFunc>
MyIter<Key, Value>
HashTable<Key, Value, HashFunc>::Insert(const Key& a_key, const Value& a_value)
{
	size_t hashValue = m_hashFunc(a_key);
	size_t index = Index(a_key);	
	iterator iterFind = this-> at(index).Find(a_key, hashValue);
	
	if(iterFind != this->at(index).End())
	{
		MyIter<Key, Value> iter(iterFind,  (this->begin() + index), this->end());
		return iter;
	}
	
	MyPair<Key, Value> myPair(a_key, a_value, hashValue);
	
	this-> at(index).PushFront(myPair);
	
	iterator iterInsert = this->at(index).Begin();
	MyIter<Key, Value> iter(iterInsert,  (this->begin() + index), this->end());
	
	++m_size;
	
	return iter;
}

template < typename Key, typename Value, typename HashFunc>
Value& HashTable<Key, Value, HashFunc>::operator[](const Key& a_key)
{
	size_t index = Index(a_key);	
	iterator iterFind = this-> at(index).Find(a_key, m_hashFunc(a_key));
	
	if(iterFind != this->at(index).End())
	{
		return iterFind->Second();
	}
	
	Bucket<Key, Value>& bucket = GetBucket(index);
	
	MyPair<Key, Value> myPair(a_key, (Value()), m_hashFunc(a_key));

	bucket.PushFront(myPair);
	++m_size;
		
	return bucket.Begin()->Second();		
}

template < typename Key, typename Value, typename HashFunc>
typename Bucket<Key, Value>::Bucket& 
HashTable<Key, Value, HashFunc>::GetBucket(size_t a_index)
{
	return this-> at(a_index);
}


template < typename Key, typename Value, typename HashFunc>
bool HashTable<Key, Value, HashFunc>::Remove(const Key& a_key, Value& a_value)
{
	size_t index = Index(a_key);
	
	iterator iterFind = this-> at(index).Find(a_key, m_hashFunc(a_key));
	
	if(iterFind == this->at(index).End())
	{
		return false;
	}		
	
	a_value = iterFind->Second();
	
	this-> at(index).Remove(a_key, m_hashFunc(a_key));
	
	--m_size;
	
	return true;
}

template < typename Key, typename Value, typename HashFunc>
MyIter<Key, Value>
HashTable<Key, Value, HashFunc>::Find(const Key& a_key)
{
	size_t index = Index(a_key);
	iterator iter = this-> at(index).Find(a_key, m_hashFunc(a_key));
	if (iter != this->at(index).End())
	{
		MyIter<Key, Value> myIter(iter,  (this->begin() + index), this->end());
		return myIter;
	}
	return End();	
}

template < typename Key, typename Value, typename HashFunc>
MyIterConst<Key, Value>
HashTable<Key, Value, HashFunc>::Find(const Key& a_key) const
{
	size_t index = Index(a_key);	
	const_iterator iter = this-> at(index).Find(a_key, m_hashFunc(a_key));
	if (iter != this-> at(index).End())
	{
		MyIterConst<Key, Value> myIter(iter,  (this->begin() + index), this->end());
		return myIter;	
	}
	return End();
}

template < typename Key, typename Value, typename HashFunc>
size_t 
HashTable<Key, Value, HashFunc>::Index(const Key& a_key) 
const
{
	return m_hashFunc(a_key) % Capacity();
}

template < typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::Capacity() const
{
	return m_capacity;
}

template < typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::Size() const
{
	return m_size;
}

template < typename Key, typename Value, typename HashFunc>
double HashTable<Key, Value, HashFunc>::LoadFactor() const
{
	return Size()/Capacity();
}

template < typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::Clear()
{
	size_t index = Capacity();
	
	while(index-- > 0)
	{
		this-> at(index).Clear();
	}	
	m_size = 0;
}


template < typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::Resize(size_t a_capacity)
{
	HashTable<Key, Value, HashFunc> newHash(a_capacity, m_hashFunc);
	
	size_t oldCapacity = Capacity();
	
	while(oldCapacity-- > 0)
	{
	    iterator begin = this-> at(oldCapacity).Begin();
		while(begin != this-> at(oldCapacity).End())
		{
			newHash.Insert(begin->First(), begin->Second()); 
			++begin;
		}		
	}
	
	Swap(newHash);
}

template < typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::Swap(HashTable& a_hash)
{
	m_capacity = a_hash.Capacity();
	std::vector<typename Bucket<Key, Value>::Bucket>::swap(a_hash);
}

template <typename Key, typename Value, typename HashFunc>
void Swap(HashTable<Key, Value, HashFunc>& a_first, HashTable<Key, Value, HashFunc>& a_second)
{
	a_first.Swap(a_second);
}


}

#endif // HASH_TABLE_HPP
