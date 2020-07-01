#ifndef SAFE_HASH_H
#define SAFE_HASH_H

#include "HashTable.hpp"
#include "mutex.hpp"
#include "Common.hpp"

namespace advcpp 
{

const size_t BaseSize = 1001;

template <typename Key, typename Value, typename HashFunc>
class SafeHash : private UnCopyable
{
public:
    SafeHash(size_t a_capacity, const HashFunc & a_hashFunc);
	~SafeHash();
	
	//	SafeHash(SafeHash & a_other); = deleted
	//	SafeHash & operator= (const SafeHash & a_other); = deleted

	
	void Insert(const Key & a_key, const Value & a_val);
	const Value & Find(const Key & a_key) const;

	template <typename Ch>
	bool Change(const Key & a_key, Ch a_change);

	template <typename Ch>
	void Upsert(const Key & a_key, Ch a_change);
	
	template <typename Ch>
	void ForEach(const Key & a_key, Ch a_change);
	
	bool ReSize(size_t a_size);
	void Clear();
	
	size_t Capacity() const;
	size_t Size() ;
	size_t LoadFactor() ;
	

private:
	HashIterator<Key, Value> find(const Key & a_key);
	void swap(SafeHash & a_other);

	void destroyMutexes();
	
	void lockdown();
	void unlockDown();

private:
    HashTable<Key, Value, HashFunc> m_table;
    size_t m_mutexes; 
    Mutex * m_cMutex;
	
};



} // namespace advcpp

#include "inl/safe_hash.inl"
#endif // SAFE_HASH_H
