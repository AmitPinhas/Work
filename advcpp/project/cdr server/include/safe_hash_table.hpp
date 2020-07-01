#ifndef SAFE_HASH_TABLE_HPP
#define SAFE_HASH_TABLE_HPP

#include "hash_table.hpp"
#include "mutex.hpp"

namespace advcpp
{
template < typename Key, typename Value, typename HashFunc>   
class SafeHashTable
{
public:
    typedef typename HashTable<Key, Value, HashFunc>::const_iterator const_iterator;

    SafeHashTable(size_t a_capacity, const HashFunc& a_hashFunc, size_t a_numThreads);

    MyIter<Key, Value> Insert(const Key& a_key, const Value& a_value);

    MyIterConst<Key, Value> Find(const Key& a_key) const;
	MyIter<Key, Value> Find(const Key& a_key);

	bool Remove(const Key& a_key, Value& a_value);
	
	Value operator[](const Key& a_key);
		
	MyIter<Key, Value> Begin();
	const_iterator Begin() const;
	
	MyIter<Key, Value> End();
	const_iterator End() const;	
	
	size_t Size() const;
	size_t Capacity() const;
	double LoadFactor() const;
	
	void Clear();

	void Resize(size_t a_capacity);
	
	void Swap(HashTable<Key, Value, HashFunc>& a_hash);

private:
    void lockAll();
    void unlockAll(); 
    void lockMutex(Mutex a_mutex);
    void unlockMutex(Mutex a_mutex);

private:
    HashTable<Key, Value, HashFunc> m_safeHash;
    HashFunc m_hashFunc;
    size_t m_capacityMutexes;
    std::vector<Mutex> m_mutexes;

};
} // namespace advcpp

#include "safe_hash_table.inl"

#endif // SAFE_HASH_TABLE_HPP