#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>

namespace advcpp
{

template < typename Key, typename Value, typename HashFunc>
class HashTable
{
public:
	struct Pair
	{
		Key m_key;
		Value m_value;
	};
	
	explicit HashTable(size_t a_capacity, const HashFunc& a_hashFunc = 0, const EqualFunc& a_equalFunc = 0);
	
	~HashTable() ;
	
	HashTable(const HashTable& a_other) ;
	
	HashTable& operator=(const HashTable& a_other) ;
	
	bool Insert(const Key& a_key, const Value& a_value);
	
	bool Find(const Key& a_key, Value& a_value) const; 
	
	bool Remove(const Key& a_key, Value& a_value) ;
	
	Value& operator[](const Key& a_key);
	const Value& operator[](const Key& a_key) const;
	
private:
	HashFunc m_hashFunc;
	EqualFunc m_equalFunc;
	size_t m_capacity;
	std::vector<Pair*> m_hashMap;		
};

}

#endif // HASH_TABLE_HPP
