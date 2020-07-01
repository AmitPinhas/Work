#ifndef HASH_TABLE_ITR_HPP
#define HASH_TABLE_ITR_HPP


#include "concurrent_hash_table.hpp"
#include "default_hasher.hpp"
#include <cstddef> //size_t
#include <cassert>

namespace advcpp
{

template< typename Key, typename Value>
class Bucket;

template<typename Key, typename Value, typename HashFunc>
class ConcurrentHashTable;

template<typename Key, typename Value, typename HashFunc>
class ConcurrentHashTableItr
{
public:
	//typedef std::bidirectional_iterator_tag iterator_category;
	//typedef Pair<Key, Value> value_type;

	ConcurrentHashTableItr(typename Bucket<Key, Value>::iterator a_itr, ConcurrentHashTable<Key, Value, HashFunc>& a_table, size_t a_index);

	ConcurrentHashTableItr& operator=(ConcurrentHashTableItr const& a_itr);

	//~ConcurrentHashTableItr() = default;
	//ConcurrentHashTableItr(const ConcurrentHashTableItr& a_seq) = default;
	//ConcurrentHashTableItr& operator=(const ConcurrentHashTableItr& a_itr) = default;
	
	ConcurrentHashTableItr& operator++();
	ConcurrentHashTableItr operator++(int);
	
	ConcurrentHashTableItr& operator--();
	ConcurrentHashTableItr operator--(int);
	
	typename Bucket<Key, Value>::iterator& Itr();
	typename Bucket<Key, Value>::iterator const& Itr() const;
	
	std::pair<const Key, Value> & operator*();
	std::pair<const Key, Value> const & operator*() const;

	std::pair<const Key, Value> * operator->();
	
	bool operator==(ConcurrentHashTableItr const & a_itr) const;
	bool operator!=(ConcurrentHashTableItr const & a_itr) const;
private:
	size_t& Index();
	size_t Index() const;
	ConcurrentHashTable<Key, Value, HashFunc>& Table();
	void* operator new(std::size_t a_size) throw(std::bad_alloc);
private:
    size_t m_index;
	typename Bucket<Key, Value>::iterator m_itr;
	ConcurrentHashTable<Key, Value, HashFunc>& m_table;
};

template<typename Key, typename Value, typename HashFunc>
std::pair<const Key, Value>*
ConcurrentHashTableItr<Key, Value, HashFunc>::operator->()
{
	return &((*Itr()).m_pair);
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableItr<Key, Value, HashFunc>::
ConcurrentHashTableItr(typename Bucket<Key, Value>::iterator a_itr, ConcurrentHashTable<Key, Value, HashFunc>& a_table, size_t a_index)
: m_index(a_index)
, m_itr(a_itr)
, m_table(a_table)
{
}

template<typename Key, typename Value, typename HashFunc>
typename Bucket<Key, Value>::iterator& 
ConcurrentHashTableItr<Key, Value, HashFunc>::Itr()
{
	return m_itr;
}

template<typename Key, typename Value, typename HashFunc>
typename Bucket<Key, Value>::iterator const& 
ConcurrentHashTableItr<Key, Value, HashFunc>::Itr() const
{
	return m_itr;
}

template<typename Key, typename Value, typename HashFunc>
size_t& ConcurrentHashTableItr<Key, Value, HashFunc>::Index()
{
        return m_index;
}

template<typename Key, typename Value, typename HashFunc>
size_t ConcurrentHashTableItr<Key, Value, HashFunc>::Index() const
{
        return m_index;
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTable<Key, Value, HashFunc>& 
ConcurrentHashTableItr<Key, Value, HashFunc>::Table()
{
        return m_table;
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableItr<Key, Value, HashFunc>& 
ConcurrentHashTableItr<Key, Value, HashFunc>::operator=(ConcurrentHashTableItr<Key, Value, HashFunc> const& a_itr)
{
    m_index = a_itr.m_index;
	m_itr = a_itr.m_itr;
	//m_table = a_itr.m_table;
	return *this;
}


template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableItr<Key, Value, HashFunc>& 
ConcurrentHashTableItr<Key, Value, HashFunc>::operator--()
{
	if(Table().IndxBucket(Index()).Begin() == Itr())
	{
	        assert(Index() > 0);
	        --Index();
	        Itr() = Table().IndxBucket(Index()).End();
	}
	else
	{
		--Itr();
	}
	
	return *this;
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableItr<Key, Value, HashFunc>
ConcurrentHashTableItr<Key, Value, HashFunc>::operator--(int)
{
    ConcurrentHashTableItr<Key, Value, HashFunc> cpy(Itr());	
	--*this;
	return cpy;	
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableItr<Key, Value, HashFunc>& 
ConcurrentHashTableItr<Key, Value, HashFunc>::operator++()
{
	if(Table().IndxBucket(Index()).End() != Itr())
	{
		++Itr();
	}
	else
	{	
		assert(Index() < Table().Capacity());
		++Index();
		Itr() = Table().IndxBucket(Index()).Begin();	
	}
	
	return *this;
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableItr<Key, Value, HashFunc>
ConcurrentHashTableItr<Key, Value, HashFunc>::operator++(int)
{
	ConcurrentHashTableItr<Key, Value, HashFunc> cpy(Itr());
	++*this;
	return cpy;	
}

template<typename Key, typename Value, typename HashFunc>
std::pair<const Key, Value>& 
ConcurrentHashTableItr<Key, Value, HashFunc>::operator*()
{
        return (*Itr()).m_pair;
}

template<typename Key, typename Value, typename HashFunc>
const std::pair<const Key, Value>& 
ConcurrentHashTableItr<Key, Value, HashFunc>::operator*() const
{
        return (*Itr()).m_pair;
}



template<typename Key, typename Value, typename HashFunc>
bool ConcurrentHashTableItr<Key, Value, HashFunc>::
operator==(const ConcurrentHashTableItr<Key, Value, HashFunc>& a_itr) const
{
	return Itr() == a_itr.Itr();
}

template<typename Key, typename Value, typename HashFunc>
bool ConcurrentHashTableItr<Key, Value, HashFunc>::
operator!=(const ConcurrentHashTableItr<Key, Value, HashFunc>& a_itr) const
{
	return Itr() != a_itr.Itr();
}

}
#endif /*HASH_TABLE_ITR_HPP*/
