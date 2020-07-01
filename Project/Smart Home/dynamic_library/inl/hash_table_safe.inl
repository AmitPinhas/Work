#ifndef HASH_TABLE_SAFE_INL
#define HASH_TABLE_SAFE_INL

#include <utility> //pair
#include <algorithm> //find
#include <vector>
#include <list>
#include <cmath> //fmod, ceil
#include <cassert>
#include "hash_table_safe.hpp"
#include "numbers.hpp" //NextPrime

namespace advcpp{

//Key should have: operator=, copy ctor, dtor, operator==
//HashFunc must get Key and return size_t

////////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename HashFunc>
HashTableSafe<Key, Value, HashFunc>::HashTableSafe(size_t a_capacity, HashFunc a_hashFunc)
: std::vector<Bucket<Key, Value> >(numbers::NextPrime(a_capacity))
, m_capacity(numbers::NextPrime(a_capacity))	
, m_hushFunc(a_hashFunc)
, m_nItems(0)
, m_mutexSize(MutexSize(a_capacity))
, m_mutex(new Mutex[m_mutexSize])
{    
}

template <typename Key, typename Value, typename HashFunc>
HashTableSafe<Key, Value, HashFunc>::~HashTableSafe()
{
    delete[] m_mutex;
}


inline  size_t MutexSize(size_t a_size)
{
	size_t size = a_size / numbers::GOLDEN_RATIO;    
    return size;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTableSafe<Key, Value, HashFunc>::MutexIndex(Key const& a_key) const
{
   return HashIndex(a_key) % m_mutexSize;
}

template <typename Key, typename Value, typename HashFunc>
bool HashTableSafe<Key, Value, HashFunc>::Find(Key const& a_key, Value& a_value)
{
    
    {
        Guard guard(m_mutex[MutexIndex(a_key)]);
        size_t index = HashIndex(a_key);
        Bucket<Key, Value>& bucket = this->at(index);
	    typename Bucket<Key, Value>::iterator found = bucket.Find(a_key);

        if (found != bucket.End())
        {
            a_value  = found->second;
            return true;
        }
        return false;
    }
}

template <typename Key, typename Value, typename HashFunc>
bool HashTableSafe<Key, Value, HashFunc>::Insert(Key const& a_key, Value const& a_value)
{
    size_t index = HashIndex(a_key);
    Bucket<Key, Value>& bucket = this->at(index);
    {
        Guard guard(m_mutex[MutexIndex(a_key)]);
        typename Bucket<Key, Value>::iterator found = bucket.Find(a_key);        
            
        // found -> return
        if (found != bucket.End())
        {
            return false;
        }        
        
        // not found -> insert
        Pair pair(a_key, a_value);
        typename Bucket<Key, Value>::iterator inserted = bucket.Insert(pair);
        assert(inserted != bucket.End());

        ++m_nItems;    	
        return true;
    }
}

template <typename Key, typename Value, typename HashFunc>
template <typename Update>
bool 
HashTableSafe<Key, Value, HashFunc>::Upsert(Key const& a_key, Value const& a_value, Update a_updater)
{
    size_t index = HashIndex(a_key);
    Bucket<Key, Value>& bucket = this->at(index);
    {
        Guard guard(m_mutex[MutexIndex(a_key)]);
        typename Bucket<Key, Value>::iterator found = bucket.Find(a_key);

        //found - do update -> true
        if (found != bucket.End())
        {
            a_updater(found->second, a_value);
            return true;
        }
        
        //not found - do insert -> false
        Pair pair(a_key, a_value);
        typename Bucket<Key, Value>::iterator inserted = bucket.Insert(pair);
        assert(inserted != bucket.End());
        
        ++m_nItems;    	
        return false;
    }
}

template <typename Key, typename Value, typename HashFunc>
bool HashTableSafe<Key, Value, HashFunc>::Remove(Key const& a_key, Value& a_value)
{
	
    size_t index = HashIndex(a_key);    
    Bucket<Key, Value>& bucket = this->at(index);
    {
        Guard guard(m_mutex[MutexIndex(a_key)]);
        typename Bucket<Key, Value>::iterator found;
        found = bucket.Find(a_key);
	
        if (found == bucket.End())
        {
            return false;
        }	
        a_value = found->second;
        bucket.Remove(found);
        --m_nItems;
    	return true;	
    }       
}

template <typename Key, typename Value, typename HashFunc>
typename HashTableSafe<Key, Value, HashFunc>::iterator HashTableSafe<Key, Value, HashFunc>::Begin()
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
typename HashTableSafe<Key, Value, HashFunc>::iterator HashTableSafe<Key, Value, HashFunc>::End()
{
    return HashItr<Key, Value>(this->at(Capacity()-1).End(), this->end(), this->end());
}


template <typename Key, typename Value, typename HashFunc>
template <typename Action>
size_t HashTableSafe<Key, Value, HashFunc>::ForEach(Action a_action)
{
    LockAll<Key, Value, HashFunc>(*this);
    {
        size_t counter = 0;
        iterator begin = Begin();
        iterator end = End();

        while(begin != end)
        {
            a_action(begin->second);
            ++begin;
            ++ counter;
        }
        return counter;
    }
}

    
template <typename Key, typename Value, typename HashFunc>
size_t HashTableSafe<Key, Value, HashFunc>::Capacity() const
{
    return m_capacity;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTableSafe<Key, Value, HashFunc>::Size() const
{
    return m_nItems.Get();    
}

template <typename Key, typename Value, typename HashFunc>
bool HashTableSafe<Key, Value, HashFunc>::IsEmpty() const
{
    size_t size = m_nItems;
    return size == 0;
}

template <typename Key, typename Value, typename HashFunc>
double HashTableSafe<Key, Value, HashFunc>::LoadFactor() const
{
    size_t size = m_nItems;
    return m_capacity / size;
    
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTableSafe<Key, Value, HashFunc>::HashIndex(Key const& a_key) const
{
    return m_hushFunc(a_key) % m_capacity;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTableSafe<Key, Value, HashFunc>::hash(Key const& a_key) const
{
   return m_hushFunc(a_key);
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTableSafe<Key, Value, HashFunc>::GetMutexSize() const
{
   return m_mutexSize;
}

////////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename HashFunc>
LockAll<Key, Value, HashFunc>::LockAll(HashTableSafe<Key, Value, HashFunc> const& a_table)
: m_table(a_table)
{    
    const size_t size = a_table.GetMutexSize();
    for (size_t i=0; i<size; ++i)
    {
        m_table.m_mutex[i].Lock();
    }
}

template <typename Key, typename Value, typename HashFunc>
LockAll<Key, Value, HashFunc>::~LockAll() noexcept
{
    const size_t size = m_table.GetMutexSize();
    for (size_t i=0; i<size; ++i)
    {
        try
        {
            m_table.m_mutex[i].Unlock();
        }
        catch(...)
        {
            throw;
        }    
    }
}

}//namespace advcpp

#endif //HASH_TABLE_SAFE_INL
