#include <utility> //pair
#include <algorithm> //find
#include <vector>
#include <list>
#include <cmath> //fmod
#include "numbers.hpp" //NextPrime
#include "bucket.hpp"

namespace advcpp{

//Key should have: operator=, copy ctor, dtor, operator==
//HashFunc must get Key and return size_t

////////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value>
class HashItr
{
public:
	typedef typename std::pair<Key, Value> Pair;

public:
    HashItr(typename Bucket<Key, Value>::iterator m_buckItr, 
			typename std::vector<Bucket<Key, Value> >::iterator m_current,
			typename std::vector<Bucket<Key, Value> >::iterator m_end);

    //HashItr(HashItr const& a_other) = default;
	//HashItr& operator=(HashItr const& a_rhs) = default;
	//~HashItr() = default;

	HashItr& operator++(); //prefix
	HashItr operator++(int); //postfix
    Pair& operator*();
	Pair* operator->();

	template <typename K, typename V>
	friend bool operator==(HashItr<K,V> a_lhs, HashItr<K,V> a_rhs);

	template <typename K, typename V>
	friend bool operator!=(HashItr<K,V> a_lhs, HashItr<K,V> a_rhs);

	template <typename K, typename V, typename H>
	friend class HashTable;

	template <typename K, typename V, typename H>
	friend class HashTableSafe;

private:
	typename Bucket<Key, Value>::iterator Itr();

private:
    typename Bucket<Key, Value>::iterator m_buckItr;
    typename std::vector<Bucket<Key, Value> >::iterator m_current;
	typename std::vector<Bucket<Key, Value> >::iterator m_end;
};

template <typename Key, typename Value>
HashItr<Key, Value>::HashItr(typename Bucket<Key, Value>::iterator a_itr, 
	typename std::vector<Bucket<Key, Value> >::iterator a_current, 
	typename std::vector<Bucket<Key, Value> >::iterator a_end)
: m_buckItr(a_itr)
, m_current(a_current)
, m_end(a_end)
{
}

template <typename Key, typename Value>
HashItr<Key, Value>& HashItr<Key, Value>::operator++()
{
	if ((++m_buckItr) != m_current->End())
	{
		return *this;
	}
	
	++m_current;
	while(m_current != m_end)
	{
		m_buckItr = m_current->Begin();
		if (m_buckItr != m_current->End())
		{
			return *this;
		}
		++ m_current;		
	}	
	
	m_buckItr = (m_end-1)->End();
	return *this;
}

template <typename Key, typename Value>
HashItr<Key, Value> HashItr<Key, Value>::operator++(int)
{
	HashItr tmpItr(*this);
	++(*this);
	return tmpItr;
}

template <typename Key, typename Value>
std::pair<Key, Value>& HashItr<Key, Value>::operator*()
{
	return *m_buckItr;
}

template <typename Key, typename Value>
std::pair<Key, Value>* HashItr<Key, Value>::operator->()
{
	return &(*m_buckItr);
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator HashItr<Key, Value>::Itr()
{
	return m_buckItr;
}

template <typename Key, typename Value>
bool operator==(HashItr<Key, Value> a_lhs, HashItr<Key, Value> a_rhs)
{
	return  a_lhs.m_buckItr == a_rhs.m_buckItr &&
			a_lhs.m_current == a_rhs.m_current  &&
			a_lhs.m_end == a_rhs.m_end;
}

template <typename Key, typename Value>
bool operator!=(HashItr<Key, Value> a_lhs, HashItr<Key, Value> a_rhs)
{
	return !(a_lhs == a_rhs);
}

////////////////////////////////////////////////////////////////////////////////

template <typename Key>
class Hasher
{
	size_t operator()(Key const& a_key);
};

template <typename Key>
size_t Hasher<Key>::operator()(Key const& a_key)
{
	return hash(a_key);
}

inline size_t hash(int a_key)
{
	return (a_key ^ 37) >> 4 ^ 0x45d9f3b; 
}

////////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename HashFunc = Hasher<Key>() >
class HashTable : private std::vector<Bucket<Key, Value> >
{
public:
	typedef typename std::pair<Key, Value> Pair;
	typedef HashItr<Key, Value> iterator;
	typedef const HashItr<Key, Value> const_iterator;

public:
	HashTable(size_t a_capacity, HashFunc a_hashFunc);
	//HashTable(HashTable const& a_other) = default;
	//HashTable& operator=(HashTable const& a_rhs) = default;
	//~HashTable() = default;

	const_iterator Find(Key const& a_key) const;
	iterator Find(Key const& a_key);
	
	iterator Insert(Key const& a_key, Value const& a_value);
	iterator Update(Key const& a_key, Value const& a_value);
	bool Remove(Key const& a_key, Value& a_value);
	//void Resize(size_t a_capacity); //TODO: it
	//void Swap(HashTable& a_other); //TODO: it

	size_t hash(Key const& a_key) const;
	
	//Value& operator[](Key const& a_key);//TODO: it
	
	size_t Capacity() const;
	size_t LoadFactor() const;
	size_t Size() const;
	bool IsEmpty() const;

	iterator Begin();
    iterator End();	

private:
	size_t HashIndex(Key const& a_key) const;	

private:
	size_t 				m_capacity;
	HashFunc 			m_hushFunc;
	size_t 				m_nItems;	
};


template <typename Key, typename Value, typename HashFunc>
HashTable<Key,Value, HashFunc>::HashTable(size_t a_capacity, HashFunc a_hashFunc)
: std::vector<Bucket<Key, Value> >(numbers::NextPrime(a_capacity)) //TODO: get prime by LUT
, m_capacity(numbers::NextPrime(a_capacity))	
, m_hushFunc(a_hashFunc)
, m_nItems(0)
{
}

template <typename Key, typename Value, typename HashFunc>
typename HashTable<Key, Value, HashFunc>::const_iterator
HashTable<Key, Value, HashFunc>::Find(Key const& a_key) const
{
	size_t index = HashIndex(a_key);
	Bucket<Key, Value> const& bucket = this->at(index);	
	return bucket.Find(a_key);
}

template <typename Key, typename Value, typename HashFunc>
typename HashTable<Key, Value, HashFunc>::iterator
HashTable<Key, Value, HashFunc>::Find(Key const& a_key)
{
	size_t index = HashIndex(a_key);
	Bucket<Key, Value>& bucket = this->at(index);
	typename Bucket<Key, Value>::iterator found = bucket.Find(a_key);
	if (found != bucket.End())
	{
		return HashItr<Key, Value>(found, this->begin()+index, this->end());
	}
	return End();
}

template <typename Key, typename Value, typename HashFunc>
typename HashTable<Key, Value, HashFunc>::iterator
HashTable<Key, Value, HashFunc>::Insert(Key const& a_key, Value const& a_value)
{
    size_t index = HashIndex(a_key);    
    Bucket<Key, Value>& bucket = this->at(index);
    typename Bucket<Key, Value>::iterator found = bucket.Find(a_key);
	    
    if (found != bucket.End())
    {
    	return End();
    }    
	
	Pair pair(a_key, a_value);
	typename Bucket<Key, Value>::iterator inserted = bucket.Insert(pair);
	++m_nItems;

	return HashItr<Key, Value>(inserted, this->begin()+index, this->end());
}

template <typename Key, typename Value, typename HashFunc>
typename HashTable<Key, Value, HashFunc>::iterator
HashTable<Key, Value, HashFunc>::Update(Key const& a_key, Value const& a_value)
{
    size_t index = HashIndex(a_key);    
    Bucket<Key, Value>& bucket = this->at(index);
    typename Bucket<Key, Value>::iterator found = bucket.Find(a_key);
	    
    if (found == bucket.End())
    {
    	return End();
    }    
	
	found->second = a_value;
	return HashItr<Key, Value>(found, this->begin()+index, this->end());
}

template <typename Key, typename Value, typename HashFunc>
bool HashTable<Key, Value, HashFunc>::Remove(Key const& a_key, Value& a_value)
{
	iterator found = Find(a_key);
	
	if (found == End())
	{
		return false;
	}	
	
	size_t index = HashIndex(a_key);
	Bucket<Key, Value>& bucket = this->at(index);

	a_value = found->second;
	bucket.Remove(found.Itr());
	--m_nItems;
	return true;	
}

/*
template <typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::Swap(HashTable& a_other)
{
	//swap vector
	//swap m_capacity, m_hushFunc, m_nItems
}

template <typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFuniterator begin this->begin();c>::Resize(size_t a_capacity)
{
	//create new HashTable
	//copy all data
	//use swap member function
}
*/

template <typename Key, typename Value, typename HashFunc>
typename HashTable<Key, Value, HashFunc>::iterator HashTable<Key, Value, HashFunc>::Begin()
{
	typename std::vector<Bucket<Key, Value> >::iterator begin = this->begin();
	typename std::vector<Bucket<Key, Value> >::iterator end = this->end();
	
	while(begin != end)
	{
		typename Bucket<Key, Value>::iterator it = begin->Begin();

		if (it != begin->End())
		{
			return HashItr<Key, Value>(it, begin, end);
		}
		++begin;
	}
	return HashItr<Key, Value>((end-1)->End(), end, end);
}

template <typename Key, typename Value, typename HashFunc>
typename HashTable<Key, Value, HashFunc>::iterator HashTable<Key, Value, HashFunc>::End()
{
	return HashItr<Key, Value>(this->at(Capacity()-1).End(), this->end(), this->end());
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::Capacity() const
{
    return m_capacity;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::Size() const
{
    return m_nItems;
}

template <typename Key, typename Value, typename HashFunc>
bool HashTable<Key, Value, HashFunc>::IsEmpty() const
{
    return 0 == m_nItems;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::LoadFactor() const
{
    return Capacity()/Size();
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::HashIndex(Key const& a_key) const
{
   return m_hushFunc(a_key) % Capacity();
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::hash(Key const& a_key) const
{
   return m_hushFunc(a_key);
}

/*
template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::hash(Key a_key)
{
	return hash(a_key); 
}
*/
}//namespace advcpp

