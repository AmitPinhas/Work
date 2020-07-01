#ifndef HASH_TABLE_CONST_ITR_HPP
#define HASH_TABLE_CONST_ITR_HPP

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

template<typename Key, typename Value, typename HashFunc >
class ConcurrentHashTableConstItr
{
public:
	//typedef std::bidirectional_iterator_tag iterator_category;
	//typedef Pair<Key, Value> value_type;

	ConcurrentHashTableConstItr(typename Bucket<Key, Value>::const_iterator a_itr, ConcurrentHashTable<Key, Value, HashFunc>const & a_table, size_t a_index);

	ConcurrentHashTableConstItr& operator=(ConcurrentHashTableConstItr const& a_itr);

	//~ConcurrentHashTableConstItr() = default;
	//ConcurrentHashTableConstItr(const ConcurrentHashTableConstItr& a_seq) = default;
	//ConcurrentHashTableConstItr& operator=(const ConcurrentHashTableConstItr& a_itr) = default;
	
	ConcurrentHashTableConstItr& operator++();
	ConcurrentHashTableConstItr operator++(int);
	
	ConcurrentHashTableConstItr& operator--();
	ConcurrentHashTableConstItr operator--(int);
	
	typename Bucket<Key, Value>::const_iterator& Itr() const;
	
	std::pair<const Key, Value> & operator*();
	std::pair<const Key, Value> const & operator*() const;

	std::pair<const Key, Value> const* operator->();
	
	bool operator==(ConcurrentHashTableConstItr const & a_itr) const;
	bool operator!=(ConcurrentHashTableConstItr const & a_itr) const;
private:
    size_t& Index();
    size_t Index() const;
    ConcurrentHashTable<Key, Value, HashFunc> & Table();
    ConcurrentHashTable<Key, Value, HashFunc> const & Table() const;
	void* operator new(std::size_t a_size) throw(std::bad_alloc);
private:
    size_t m_index;
	typename Bucket<Key, Value>::const_iterator m_itr;
	const ConcurrentHashTable<Key, Value, HashFunc>& m_table;
};

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableConstItr<Key, Value, HashFunc>::
ConcurrentHashTableConstItr(typename Bucket<Key, Value>::const_iterator a_itr, ConcurrentHashTable<Key, Value, HashFunc>const & a_table, size_t a_index)
: m_index(a_index)
, m_itr(a_itr)
, m_table(a_table)
{
}

template<typename Key, typename Value, typename HashFunc>
typename Bucket<Key, Value>::const_iterator& 
ConcurrentHashTableConstItr<Key, Value, HashFunc>::Itr() const
{
	return m_itr;
}

template<typename Key, typename Value, typename HashFunc>
size_t& ConcurrentHashTableConstItr<Key, Value, HashFunc>::Index()
{
        return m_index;
}

template<typename Key, typename Value, typename HashFunc>
size_t ConcurrentHashTableConstItr<Key, Value, HashFunc>::Index() const
{
        return m_index;
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTable<Key, Value, HashFunc>& 
ConcurrentHashTableConstItr<Key, Value, HashFunc>::Table()
{
        return m_table;
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTable<Key, Value, HashFunc> const& 
ConcurrentHashTableConstItr<Key, Value, HashFunc>::Table() const
{
        return m_table;
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableConstItr<Key, Value, HashFunc>& 
ConcurrentHashTableConstItr<Key, Value, HashFunc>::operator=(ConcurrentHashTableConstItr<Key, Value, HashFunc> const& a_itr)
{
    m_index = a_itr.m_index;
	m_itr = a_itr.m_itr;
	m_table = a_itr.m_table;
	return *this;
}


template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableConstItr<Key, Value, HashFunc>& 
ConcurrentHashTableConstItr<Key, Value, HashFunc>::operator--()
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
ConcurrentHashTableConstItr<Key, Value, HashFunc>
ConcurrentHashTableConstItr<Key, Value, HashFunc>::operator--(int)
{
    ConcurrentHashTableConstItr<Key, Value, HashFunc> cpy(Itr());	
	--*this;
	return cpy;	
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableConstItr<Key, Value, HashFunc>& 
ConcurrentHashTableConstItr<Key, Value, HashFunc>::operator++()
{
	if(Table().IndxBucket(Index()).End() == Itr())
	{
	        assert(Index() < Table().Capacity());
	        ++Index();
	        Itr() = Table().IndxBucket(Index()).Begin();  
	}
	else
	{
		++Itr();
	}
	
	
	return *this;
}

template<typename Key, typename Value, typename HashFunc>
ConcurrentHashTableConstItr<Key, Value, HashFunc>
ConcurrentHashTableConstItr<Key, Value, HashFunc>::operator++(int)
{
	ConcurrentHashTableConstItr<Key, Value, HashFunc> cpy(Itr());
	++*this;
	return cpy;	
}

template<typename Key, typename Value, typename HashFunc>
std::pair<const Key, Value> const *
ConcurrentHashTableConstItr<Key, Value, HashFunc>::operator->()
{
	return &((*Itr()).m_pair);
}

template<typename Key, typename Value, typename HashFunc>
std::pair<const Key, Value>& 
ConcurrentHashTableConstItr<Key, Value, HashFunc>::operator*()
{
        return (*Itr()).m_pair;
}

template<typename Key, typename Value, typename HashFunc>
const std::pair<const Key, Value>& 
ConcurrentHashTableConstItr<Key, Value, HashFunc>::operator*() const
{
        return (*Itr()).m_pair;
}

template<typename Key, typename Value, typename HashFunc>
bool ConcurrentHashTableConstItr<Key, Value, HashFunc>::
operator==(const ConcurrentHashTableConstItr<Key, Value, HashFunc>& a_itr) const
{
	return Itr() == a_itr.Itr();
}

template<typename Key, typename Value, typename HashFunc>
bool ConcurrentHashTableConstItr<Key, Value, HashFunc>::
operator!=(const ConcurrentHashTableConstItr<Key, Value, HashFunc>& a_itr) const
{
	return Itr() != a_itr.Itr();
}

}
#endif /*HASH_TABLE_CONST_ITR_HPP*/
