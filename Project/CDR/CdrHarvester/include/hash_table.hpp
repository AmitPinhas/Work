#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstdlib>
#include <cassert>
#include <utility>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

#include "bucket.hpp"
#include "utils.hpp"
#include "common.hpp"
#include "mutex.hpp"
#include "exeption.hpp"



namespace advcpp
{


template <typename Key, typename Value, typename HashFunc> 
class HashTable : private std::vector< Bucket<Key, Value> > 
{

public:
	HashTable(size_t a_capacity, size_t a_noThreads, HashFunc a_hashFunc = Hasher< Key >());
	~HashTable() NO_EXEPTION;

	Iterator<Key, Value> Insert(Key const& a_key, Value const& a_value);
	bool Remove(Key const& a_key, Value& a_value);

	Const_iterator<Key, Value> Find(Key const& a_key) const NO_EXEPTION;
	Iterator<Key, Value> Find(Key const& a_key) NO_EXEPTION;

	Value& operator[](Key const& a_key) NO_EXEPTION;
	Value const& operator[](Key const& a_key) const NO_EXEPTION;

	void ReSize(size_t a_newCap);

	size_t Size() const NO_EXEPTION;
	size_t Capacity() const NO_EXEPTION;
	double LoadFactor() const NO_EXEPTION;

	void Swap(HashTable<Key, Value, HashFunc>& a_lhs) NO_EXEPTION;

	void Clear() NO_EXEPTION;

	template<typename Functor>
	void ForEach(Functor a_func);

private:
	size_t FindIndex(Key const& a_key) const NO_EXEPTION;
	size_t FindMutexIndex(size_t a_index) const NO_EXEPTION;

private:
	size_t m_size;
	size_t m_capacity;
	HashFunc m_hashFunc;
	std::vector<Mutex*> m_keys;
};
}// end advcpp namespace

#include "inl/hash_table.inl"

#endif //HASH_TABLE_HPP
