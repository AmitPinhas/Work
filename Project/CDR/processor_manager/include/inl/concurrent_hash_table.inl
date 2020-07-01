#ifndef HASH_TABLE_INL
#define HASH_TABLE_INL


#include <cstddef> //size_t
#include <algorithm> // find_if, for_each
#include <cassert>

#include "util.hpp"
#include "util_functions.hpp"

namespace advcpp
{

template <typename Value, typename Key>
struct CopyValue;
template <typename Value, typename Key>
struct CopyBucket;

const size_t  MUTEX_NUMBER = 11;

template< typename Key, typename Value, typename Hasher>
Bucket<Key, Value> const&
ConcurrentHashTable<Key, Value, Hasher>::IndxBucket(size_t a_indx) const
{
	return this->at(a_indx);
}

template< typename Key, typename Value, typename Hasher>
Bucket<Key, Value>&
ConcurrentHashTable<Key, Value, Hasher>::IndxBucket(size_t a_indx)
{
	return this->at(a_indx);
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTable<Key, Value, Hasher>::ConcurrentHashTable(size_t a_capacity, Hasher a_func)
: std::vector<Bucket<Key, Value> >(numbers::FindNextPrime(a_capacity))
, m_capacity(numbers::FindNextPrime(a_capacity))
, m_size(0)
, m_hashFunc(a_func)
, m_vecMutex()
{
	fillMutexVector(m_vecMutex);
}

template< typename Key, typename Value, typename Hasher>
void ConcurrentHashTable<Key, Value, Hasher>::fillMutexVector(std::vector<Mutex*>& a_vecMutex)
{
	const size_t mutexVecSize = MUTEX_NUMBER;
	for(size_t i = 0; i < mutexVecSize; ++i)
	{
		a_vecMutex.push_back(new Mutex());
	}
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTable<Key, Value, Hasher>::~ConcurrentHashTable() NOEXCEPT
{
	for(size_t i = 0; i < m_vecMutex.size(); ++i)
	{
		delete m_vecMutex[i];
	}
}



template< typename Key, typename Value, typename Hasher>
const Bucket<Key, Value>&
ConcurrentHashTable<Key, Value, Hasher>::GetBucket(const Key& a_key) const
{
	size_t indx = calculateIndex(a_key);
    return std::vector<Bucket<Key, Value> >::operator[](indx);
}

template< typename Key, typename Value, typename Hasher>
Bucket< Key, Value>&
ConcurrentHashTable<Key, Value, Hasher>::getBucket(const Key& a_key)
{
    return const_cast<Bucket< Key, Value> &>(this->GetBucket(a_key));
}

template< typename Key, typename Value, typename Hasher>
const Hasher& ConcurrentHashTable<Key, Value, Hasher>::hash() const
{
	return m_hashFunc;
}

template< typename Key, typename Value, typename Hasher>
size_t ConcurrentHashTable<Key, Value, Hasher>::Size() const
{
	return m_size;
}

template< typename Key, typename Value, typename Hasher>
size_t ConcurrentHashTable<Key, Value, Hasher>::Capacity() const
{
	return m_capacity;
}

template< typename Key, typename Value, typename Hasher>
float ConcurrentHashTable<Key, Value, Hasher>::LoadFactor() const
{
    assert(Capacity() != 0);
    return static_cast<float>(m_size) / m_capacity;
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTableItr<Key, Value, Hasher>
ConcurrentHashTable<Key, Value, Hasher>::Begin()
{
	return ConcurrentHashTableItr<Key, Value, Hasher>(this->begin()->Begin(),*this ,0);
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTableItr<Key, Value, Hasher>
ConcurrentHashTable<Key, Value, Hasher>::End()
{
	return ConcurrentHashTableItr<Key, Value, Hasher>((this->end()-1)->End(), *this, Capacity() - 1);
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTableConstItr<Key, Value, Hasher>
ConcurrentHashTable<Key, Value, Hasher>::Begin() const
{
	return ConcurrentHashTableConstItr<Key, Value, Hasher>(this->begin()->Begin(),*this ,0);
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTableConstItr<Key, Value, Hasher>
ConcurrentHashTable<Key, Value, Hasher>::End() const
{
	return ConcurrentHashTableConstItr<Key, Value, Hasher>((this->end()-1)->End(), *this, Capacity() - 1);
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTableItr<Key, Value, Hasher>
ConcurrentHashTable<Key, Value, Hasher>::
Insert(const Key& a_key, const Value& a_val)
{
	size_t indxMutex = calculateIndexMutex(a_key);
	Guard locker(*m_vecMutex[indxMutex]);
	Bucket<Key, Value>& bucket = getBucket(a_key);
	typename Bucket<Key, Value>::iterator it = bucket.Insert(a_key, a_val , hash()(a_key));
	if(it != bucket.End())
	{
		++m_size;
		return ConcurrentHashTableItr<Key, Value, Hasher>(it, *this, calculateIndex(a_key));
	}

    return End();
}


template<typename Key, typename Value, typename Hasher>
template<typename Update>
ConcurrentHashTableItr<Key, Value, Hasher> ConcurrentHashTable<Key, Value, Hasher>::
Upsert(const Key& a_key, const Value& a_val, Update a_update)
{
	size_t indxMutex = calculateIndexMutex(a_key);
	Guard locker(*m_vecMutex[indxMutex]);
	Bucket<Key, Value>& bucket = getBucket(a_key);
	typename Bucket<Key, Value>::iterator it = bucket.Find(a_key, hash()(a_key));
	if(it == bucket.End())
	{
		++m_size;
		it = bucket.Insert(a_key, a_val, hash()(a_key));
	}
	else
	{
		a_update(it->m_pair.second, a_val);
	}

	return ConcurrentHashTableItr<Key, Value, Hasher>(it, *this, calculateIndex(a_key));
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTableConstItr<Key, Value, Hasher>
ConcurrentHashTable<Key, Value, Hasher>::Find(const Key& a_key) const
{
	size_t indxMutex = calculateIndexMutex(a_key);
	Guard locker(*m_vecMutex[indxMutex]);
	const Bucket<Key, Value>& bucket = GetBucket(a_key);
	typename Bucket<Key, Value>::const_iterator it = bucket.Find(a_key, hash()(a_key));
	if(it == bucket.End())
	{
	        return End();
	}

	return ConcurrentHashTableConstItr<Key, Value, Hasher>(it, *this, calculateIndex(a_key));
}

template< typename Key, typename Value, typename Hasher>
ConcurrentHashTableItr<Key, Value, Hasher>
ConcurrentHashTable<Key, Value, Hasher>::Find(const Key& a_key)
{
	size_t indxMutex = calculateIndexMutex(a_key);
	Guard locker(*m_vecMutex[indxMutex]);
	Bucket<Key, Value>& bucket = getBucket(a_key);
	typename Bucket<Key, Value>::iterator it = bucket.Find(a_key, hash()(a_key));
	if(it == bucket.End())
	{
	        return End();
	}

	return ConcurrentHashTableItr<Key, Value, Hasher>(it, *this, calculateIndex(a_key));
}

template< typename Key, typename Value, typename Hasher>
bool ConcurrentHashTable<Key, Value, Hasher>::Find(const Key& a_key, Value& a_val) const
{
	size_t indxMutex = calculateIndexMutex(a_key);
	Guard locker(*m_vecMutex[indxMutex]);
	const Bucket<Key, Value>& bucket = GetBucket(a_key);
	typename Bucket<Key, Value>::const_iterator it = bucket.Find(a_key, hash()(a_key));
	if(it == bucket.End())
	{
	        return false;
	}

	a_val = it->m_pair.second;
	return true;
}


template< typename Key, typename Value, typename Hasher>
Value& ConcurrentHashTable<Key, Value, Hasher>::operator[](const Key& a_key)
{
	size_t indxMutex = calculateIndexMutex(a_key);
	Guard locker(*m_vecMutex[indxMutex]);
    Bucket<Key, Value>& bucket = getBucket(a_key);
    typename Bucket<Key, Value>::iterator it = bucket.Find(a_key, hash()(a_key));
    if(it == bucket.End())
    {
        Value val;
        it = bucket.Insert(a_key, val, hash()(a_key));
    }

    assert(it != bucket.End());
    return (*it).m_pair.second;
}

template< typename Key, typename Value, typename Hasher>
bool ConcurrentHashTable<Key, Value, Hasher>::Remove(const Key& a_key, Value& a_val)
{
	size_t indxMutex = calculateIndexMutex(a_key);
	Guard locker(*m_vecMutex[indxMutex]);
    Bucket<Key, Value>& bucket = getBucket(a_key);
    return bucket.Remove(a_key, a_val, hash()(a_key));
}

template< typename Key, typename Value, typename Hasher>
size_t ConcurrentHashTable<Key, Value, Hasher>::calculateIndex(const Key& a_key) const
{
	return hash()(a_key) % Capacity();
}

template< typename Key, typename Value, typename Hasher>
size_t ConcurrentHashTable<Key, Value, Hasher>::calculateIndexMutex(const Key& a_key) const
{
	return hash()(a_key) % m_vecMutex.size();
}


template< typename Key, typename Value, typename Hasher>
void ConcurrentHashTable<Key, Value, Hasher>::Insert(const Key& a_key, const Value& a_val, size_t a_hashVal)
{
     Bucket<Key, Value>& bucket = getBucket(a_key);
     bucket.Insert(a_key, a_val, a_hashVal);
}

template< typename Key, typename Value, typename Hasher>
void ConcurrentHashTable<Key, Value, Hasher>::
copyConcurrentHashTable(ConcurrentHashTable<Key, Value, Hasher>& a_target, const ConcurrentHashTable<Key, Value, Hasher>& a_origin)
{
	for(size_t i = 0; i < a_origin.Capacity(); ++i)
	{
		typename Bucket<Key, Value>::const_iterator it = a_origin.at(i).Begin();
		typename Bucket<Key, Value>::const_iterator end = a_origin.at(i).End();
		while(it != end)
		{
			a_target.Insert(it->m_pair.first, it->m_pair.second, it->HashValue());
			++it;
		}
	}
}

template< typename Key, typename Value, typename Hasher>
void ConcurrentHashTable<Key, Value, Hasher>::swap(ConcurrentHashTable<Key, Value, Hasher>& a_origin)
{
    cpp::Swap(m_size, a_origin.m_size);
    cpp::Swap(m_hashFunc, a_origin.m_hashFunc);
    cpp::Swap(this->m_capacity, a_origin.m_capacity);
    std::vector<Bucket< Key, Value> >::swap(a_origin);
}

template< typename Key, typename Value, typename Hasher>
void ConcurrentHashTable<Key, Value, Hasher>::Resize(size_t a_newCapacity)
{
	size_t capacity = numbers::FindNextPrime(a_newCapacity);
	ConcurrentHashTable<Key, Value, Hasher> newTable(capacity, hash());
	copyConcurrentHashTable(newTable, *this);
	swap(newTable);
}

template< typename Key, typename Value>
static void ClearBucket(Bucket<Key, Value>& a_bucket)
{
    a_bucket.Clear();
}

template< typename Key, typename Value, typename Hasher>
void ConcurrentHashTable<Key, Value, Hasher>::Clear()
{
	GuardAll lockAll(m_vecMutex);
	for_each(this->begin(), this->end(), static_cast<void (*)(Bucket<Key, Value>&)>(ClearBucket));
    m_size = 0;
}

template< typename Key, typename Value, typename Hasher>
void ConcurrentHashTable<Key, Value, Hasher>::CopyAllTable(std::vector<Value>& a_vectorToFill) const
{
	GuardAll lockAll(m_vecMutex);
	for_each(this->begin(), this->end(), CopyBucket<Value, Key>(a_vectorToFill));
}

template <typename Value, typename Key>
struct CopyValue
{
	CopyValue(std::vector<Value>& a_vectorToFill)
	: vecToFill(a_vectorToFill)
	{
	}

	void operator()(Pair< Key, Value> const& a_pair)
	{
		vecToFill.push_back(a_pair.m_pair.second);
	}

	std::vector<Value>& vecToFill;
};


template <typename Value, typename Key>
struct CopyBucket
{
	CopyBucket(std::vector<Value>& a_vectorToFill)
	: vecToFill(a_vectorToFill)
	{
	}

	void operator()(Bucket< Key, Value> const & a_bucket)
	{
		for_each(a_bucket.Begin(), a_bucket.End(), CopyValue<Value, Key>(vecToFill));
	}

	std::vector<Value>& vecToFill;
};



///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

template< typename Key, typename Value>
std::list<Pair<const Key, Value> >&
Bucket<Key, Value>::Container()
{
    return m_bucket;
}

template< typename Key, typename Value>
const std::list<Pair<const Key, Value> >&
Bucket< Key, Value>::Container() const
{
    return m_bucket;
}

template< typename Key, typename Value>
typename Bucket< Key, Value>::iterator
Bucket<Key, Value>::Begin()
{
    return Container().begin();
}

template< typename Key, typename Value>
typename Bucket<Key, Value>::iterator
Bucket< Key, Value>::End()
{
    return Container().end();
}

template< typename Key, typename Value>
typename Bucket< Key, Value>::const_iterator
Bucket< Key, Value>::Begin() const
{
    return Container().begin();
}

template< typename Key, typename Value>
typename Bucket< Key, Value>::const_iterator
Bucket< Key, Value>::End() const
{
    return Container().end();
}

template< typename Key, typename Value>
struct KeyCmp
{

KeyCmp(const Key& a_key, size_t a_hVal)
: m_key(a_key)
, m_hVal(a_hVal)
{
}

bool operator()(const Pair<const Key, Value>& a_lhs)
{
    if(m_hVal == a_lhs.HashValue())
    {
        return m_key == a_lhs.m_pair.first;
    }

    return false;
}

const Key& m_key;
size_t m_hVal;

};

template< typename Key, typename Value>
typename Bucket< Key, Value>::iterator
Bucket< Key, Value>::Insert(const Key& a_key, const Value& a_val, size_t a_hVal)
{
	iterator it = Find(a_key, a_hVal);
	if(it == End())
	{
		Pair<const Key, Value> myPair(a_key, a_val, a_hVal);
		return Container().insert(Begin(), myPair);
	}

	return End();
}

template< typename Key, typename Value>
typename Bucket< Key, Value>::iterator
Bucket< Key, Value>::Find(const Key& a_key, size_t a_hVal)
{
     return std::find_if(Begin(), End(), KeyCmp<Key, Value>(a_key, a_hVal));
}

template< typename Key, typename Value>
typename Bucket< Key, Value>::const_iterator
Bucket< Key, Value>::Find(const Key& a_key, size_t a_hVal) const
{
    return std::find_if(Begin(), End(), KeyCmp<Key, Value>(a_key, a_hVal));
}

template< typename Key, typename Value>
bool Bucket< Key, Value>::Remove(const Key& a_key, Value& a_val, size_t a_hVal)
{
    iterator it = Find(a_key, a_hVal);
    if(it != End())
    {
        a_val = it->m_pair.second;
        Container().erase(it);
        return true;
    }

    return false;
}

template< typename Key, typename Value>
void Bucket< Key, Value>::Clear()
{
    Container().clear();
}

template< typename Key, typename Value>
Pair<Key, Value>::Pair(const Key& a_key, const Value& a_value, size_t a_hashVal)
: m_pair(a_key, a_value)
, m_hashValue(a_hashVal)
{
}

template< typename Key, typename Value>
size_t Pair<Key, Value>::HashValue() const
{
    return m_hashValue;
}

template< typename Key, typename Value, typename Hasher>
void swap(ConcurrentHashTable<Key, Value, Hasher>& a_tableA, ConcurrentHashTable<Key, Value, Hasher>& a_tableB)
{
    a_tableA.swap(a_tableB);
}

} //namespace advcpp

#endif //HASH_TABLE_INL
