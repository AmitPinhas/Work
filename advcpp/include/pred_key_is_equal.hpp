#ifndef PRED_PAIR_HPP
#define PRED_PAIR_HPP

#include "my_pair.hpp"

namespace advcpp
{

template <typename Key, typename Value>
class PairKeyIsEqual
{
public:
	explicit PairKeyIsEqual(const Key& a_key, size_t a_hashValue);
	
	bool operator()(const MyPair<Key, Value>& a_pair) const;
	
private:
	const Key& m_key;
	size_t m_hashValue;	
};

template <typename Key, typename Value>
PairKeyIsEqual<Key, Value>::PairKeyIsEqual(const Key& a_key, size_t a_hashValue)
: m_key(a_key)
, m_hashValue(a_hashValue)
{
}

template <typename Key, typename Value>
bool PairKeyIsEqual<Key, Value>::operator()(const MyPair<Key, Value>& a_pair) const
{
	if(a_pair.m_third != m_hashValue)
	{
		return false;
	}
	return m_key == a_pair.First();
}

}

#endif // PRED_PAIR_HPP
