#ifndef HASH_TABLE_SAFE_HPP
#define HASH_TABLE_SAFE_HPP

#include <utility> //pair
#include <algorithm> //find
#include <deque>
#include <vector>
#include <list>
#include <cmath> //fmod
#include "hash_table.hpp" //HashItr, Hasher
#include "bucket.hpp"
#include "mutex.hpp"
#include "atomic.hpp"

namespace advcpp{

//Key should have: operator=, copy ctor, dtor, operator==
//HashFunc must get Key and return size_t

////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Value, typename HashFunc>
class LockAll;

size_t MutexSize(size_t a_size);

template <typename Key, typename Value, typename HashFunc = Hasher<Key>() >
class HashTableSafe : private std::vector<Bucket<Key, Value> >
{
public:
    typedef typename std::pair<Key, Value> Pair;    
	typedef HashItr<Key, Value> iterator;
	typedef const HashItr<Key, Value> const_iterator;

public:
	HashTableSafe(size_t a_capacity, HashFunc a_hashFunc);
	~HashTableSafe();

private:
	HashTableSafe(HashTableSafe const& a_other);
	HashTableSafe& operator=(HashTableSafe const& a_rhs);

public:
	bool Find(Key const& a_key, Value& a_value);

	bool Insert(Key const& a_key, Value const& a_value);
	
    template <typename Update>
    bool Upsert(Key const& a_key, Value const& a_value, Update a_update);   //update: true, insert: false
	
	bool Remove(Key const& a_key, Value& a_value);
    	
	template <typename Action>
	size_t ForEach(Action a_action);

	
	size_t hash(Key const& a_key) const;
	size_t Capacity() const;
	double LoadFactor() const;
	size_t Size() const;
	bool IsEmpty() const;

    template <typename K, typename V, typename H>
    friend class LockAll;

private:
	iterator Begin();
    iterator End();
	size_t HashIndex(Key const& a_key) const;	
	size_t MutexIndex(Key const& a_key) const;
    size_t GetMutexSize() const;

private:
	size_t 		    	m_capacity;
	HashFunc 	    	m_hushFunc;
	AtomicValue<size_t>	m_nItems;	//TODO:change to atomic
    size_t          	m_mutexSize;
	mutable Mutex*  	m_mutex;
};

////////////////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename HashFunc>
class LockAll 
{
public:
    LockAll(HashTableSafe<Key, Value, HashFunc> const& a_table);
    ~LockAll() noexcept;

private:
    HashTableSafe<Key, Value, HashFunc> const&  m_table;
};

}//namespace advcpp
#include "inl/hash_table_safe.inl"
#endif //HASH_TABLE_SAFE_HPP
