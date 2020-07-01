#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <vector>
#include <list>
#include <cstdlib>
//#include "HashPair.hpp"
#include "HashIterator.hpp"
#include "Buckets.hpp"
#include "Numbers.hpp"
#include "Prime.hpp"
#include "HashCap.hpp"

namespace advcpp
{




const size_t PRIME_LIMIT = 100000;
const size_t DEFAULT_PRIME = 587;



template <typename Key, typename Value, typename HashFunc>
// key must have == operator
// value must have default constructor
class HashTable : private std::vector<Bucket<HashCap<Key,Value>, Key> > 
{
public:
	typedef std::vector<std::list<HashCap<Key, Value> > > Table;
	typedef typename std::list<HashCap<Key, Value> >::iterator LIter;
	typedef typename std::vector<Bucket<HashCap<Key,Value>, Key> >::iterator VIter;
	
	HashTable(size_t a_capacity, const HashFunc & a_hashFunc);
	//	HashTable(HashTable & a_other);
	//	~HashTable();
	//	HashTable & operator= (const HashTable & a_other);
	
	HashIterator<Key, Value> Insert(const Key & a_key, const Value & a_val);
	bool Remove(const Key & a_key, HashCap<Key, Value> & a_pair); // default Error Pair if no pair was found
	HashIterator<Key, Value> Find(const Key & a_key);
	HashIteratorConst<Key, Value> Find(const Key & a_key) const;

	Value & operator[] (const Key & a_key);
	
	bool ReSize(size_t a_size);
	void Clear();
	
	HashIterator<Key, Value> Begin();
	HashIterator<Key, Value> End();

	HashIteratorConst<Key, Value> Begin() const;
	HashIteratorConst<Key, Value> End() const;
	
	size_t Capacity() const;
	size_t Size() const;
	size_t LoadFactor() const;
	
	void Swap(HashTable & a_other);

	size_t HashIt(const Key & a_key) const;

private:
	void Fill(HashTable & a_other);
	size_t GetCapacity(size_t a_capacity);
	
private:
	size_t m_capacity;
	HashFunc m_hashFunc;
	size_t m_size;
};

template <typename Key, typename Value, typename HashFunc>
HashTable<Key, Value, HashFunc>::HashTable(size_t a_capacity, const HashFunc & a_hashFunc)
: std::vector<Bucket<HashCap<Key,Value>, Key> >(numbers::NextPrime(a_capacity)+1)
, m_capacity(GetCapacity(a_capacity))
, m_hashFunc(a_hashFunc)
, m_size(0)
{	
	HashCap<Key, Value> newCap;
	this -> at(m_capacity).Insert(newCap);
}

template <typename Key, typename Value, typename HashFunc>
HashIteratorConst<Key, Value> HashTable<Key, Value, HashFunc>::Find(const Key & a_key) const
{
	typedef typename std::list<HashCap<Key, Value> >::const_iterator Iter;
	typedef typename std::vector<Bucket<HashCap<Key,Value>, Key> >::const_iterator VIter;
	size_t index = m_hashFunc(a_key) % m_capacity;
	Iter it = this -> at(index).Find(a_key, m_hashFunc(a_key));
	Iter end = this -> at(index).End();
	
	if(end == it)
	{
		it = this -> at(m_capacity).End();
		index = m_capacity;
	}
	
	VIter vit = this -> begin();
	vit += index;
	HashIteratorConst<Key, Value> constIter(it, vit);
	return constIter;
}

template <typename Key, typename Value, typename HashFunc>
HashIterator<Key, Value> HashTable<Key, Value, HashFunc>::Find(const Key & a_key) 
{ 
	
	size_t index = m_hashFunc(a_key) % m_capacity;
	LIter it = this -> at(index).Find(a_key, m_hashFunc(a_key));
	LIter end = this -> at(index).End();
	
	if(end == it)
	{
		return End();
	}
	
	VIter vit = this -> begin();
	vit += index;
	HashIterator<Key, Value> Iter(it, vit);	
	return Iter;
}


template <typename Key, typename Value, typename HashFunc>
HashIterator<Key, Value> HashTable<Key, Value, HashFunc>::Insert(const Key & a_key, const Value & a_val)
{
	Pair<Key, Value> keyval(a_key, a_val);
	HashCap<Key, Value> HC(keyval, m_hashFunc(a_key));
	size_t index = m_hashFunc(a_key) % m_capacity;
	LIter it = this -> at(index).Find(a_key, m_hashFunc(a_key));
	LIter end = this -> at(index).End();
	
	if(end == it)
	{
		++m_size;
		it = this -> at(index).Insert(HC);
		VIter vit = this -> begin();
		vit += index;
		HashIterator<Key, Value> Iter(it, vit);
		
		return Iter;
	}
	
	return End();	
}

template <typename Key, typename Value, typename HashFunc>
HashIterator<Key, Value> HashTable<Key, Value, HashFunc>::Begin()
{
	VIter vit = this -> begin();
	LIter it = vit -> Begin();
	LIter end = vit -> End();
	
	while(end == it)
	{
		end = (*(++vit)).End();
		it = (*vit).Begin();
	}
	
	
	HashIterator<Key, Value> Iter(it, vit);	
	return Iter;
}

template <typename Key, typename Value, typename HashFunc>
HashIterator<Key, Value> HashTable<Key, Value, HashFunc>::End()
{
	typedef typename std::list<HashCap<Key, Value> >::iterator LIter;
	typedef typename std::vector<Bucket<HashCap<Key,Value>, Key> >::iterator VIter;
	
	VIter vit = this -> begin();
	LIter it = this -> at(m_capacity).Begin();
	vit += m_capacity;
	HashIterator<Key, Value> Iter(it, vit);	
	return Iter;
}

template <typename Key, typename Value, typename HashFunc>
HashIteratorConst<Key, Value> HashTable<Key, Value, HashFunc>::Begin() const
{
	typedef typename std::list<HashCap<Key, Value> >::const_iterator LIter;
	typedef typename std::vector<Bucket<HashCap<Key,Value>, Key> >::const_iterator VIter;
	
	VIter vit = this -> begin();
	LIter it = vit -> Begin();
	LIter end = vit -> End();
	
	while(end == it)
	{
		end = (*(++vit)).End();
		it = (*vit).Begin();
	}
	
	
	HashIteratorConst<Key, Value> Iter(it, vit);	
	return Iter;
}


template <typename Key, typename Value, typename HashFunc>
HashIteratorConst<Key, Value> HashTable<Key, Value, HashFunc>::End() const
{
	typedef typename std::list<HashCap<Key, Value> >::const_iterator LIter;
	typedef typename std::vector<Bucket<HashCap<Key,Value>, Key> >::const_iterator VIter;
	VIter vit = this -> begin();
	LIter it = this -> at(m_capacity).Begin();
	vit += m_capacity;
	HashIteratorConst<Key, Value> Iter(it, vit);	
	return Iter;
}


template <typename Key, typename Value, typename HashFunc>
bool HashTable<Key, Value, HashFunc>::Remove(const Key & a_key, HashCap<Key, Value> & a_pair)
{
	size_t index = m_hashFunc(a_key) % m_capacity;
	
	if(this -> at(index).Remove(a_key, m_hashFunc(a_key), a_pair))
	{
		--m_size;
		return true;	
	}
	
	return false;
}


template <typename Key, typename Value, typename HashFunc>
Value & HashTable<Key, Value, HashFunc>::operator[] (const Key & a_key)
{
	Value val;
	HashIterator<Key, Value> it = Find(a_key);
	HashIterator<Key, Value> end = End();
	if(end == it)
	{
		it = Insert(a_key, val);
	}
	
	return (*it).m_value;
}


template <typename Key, typename Value, typename HashFunc>
bool HashTable<Key, Value, HashFunc>::ReSize(size_t a_size)
{
	HashTable<Key, Value, HashFunc> newHash(a_size, m_hashFunc);
	
	Fill(newHash);
	
	if(this -> Size() != newHash.Size())
	{
		return false;
	}
	
	Swap(newHash);
	return true;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::Capacity() const
{
	return m_capacity;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::Size() const
{
	return m_size;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::LoadFactor() const
{
	return m_size / m_capacity;
}


template <typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::Clear() 
{
	size_t index = m_capacity;
	while(index-- > 0)
	{
		this -> at(index).Clear();
	}
	m_size = 0;
}

template <typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::Fill(HashTable & a_other)
{
	typedef typename std::list<HashCap<Key, Value> > ::iterator Iter;
	
	for(size_t i = 0; i < m_capacity; ++i)
	{
		Iter j = (this -> at(i)).Begin();
		while(j != (this -> at(i)).End())
		{
			a_other.Insert((*j).m_pair.m_key, (*j).m_pair.m_value);
			++j;
		}
	}
	
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::GetCapacity(size_t a_capacity)
{
	static Prime prime(PRIME_LIMIT);
	
	return prime.GetNextPrime(a_capacity);
}

template <typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::Swap(HashTable & a_other)
{
	std::swap(m_capacity, a_other.m_capacity);
	std::swap(m_size, a_other.m_size);
	std::swap(m_hashFunc, a_other.m_hashFunc);
	std::vector<Bucket<HashCap<Key,Value>, Key> >::swap(a_other);
}

template <typename Key, typename Value, typename HashFunc>
void Swap(HashTable<Key, Value, HashFunc> & a_first,
HashTable<Key, Value, HashFunc> & a_second)
{
	a_first.Swap(a_second);
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::HashIt(const Key & a_key) const 
{
	return m_hashFunc(a_key);
}


}


#endif // HASH_TABLE_HPP
