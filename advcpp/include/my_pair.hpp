#ifndef MY_PAIR_H
#define MY_PAIR_H

#include <utility> // std::pair

namespace advcpp
{

template <typename Key, typename Value>
class MyPair
{
public:
	MyPair(const Key& a_key, const Value& a_value, size_t a_third);
	
	Key& First();
	const Key& First() const;
	Value& Second();
	const Value& Second() const;
	
	template <typename A, typename B>
	friend class PairKeyIsEqual;
	
private:
	std::pair<Key, Value> m_pair;
	size_t m_third;
};

template <typename Key, typename Value>
MyPair<Key, Value>::MyPair(const Key& a_key, const Value& a_value, size_t a_third)
: m_pair(a_key, a_value)
, m_third(a_third)
{
}

template <typename Key, typename Value>
Key& MyPair<Key, Value>::First()
{
	return m_pair.first;
}

template <typename Key, typename Value>
const Key& MyPair<Key, Value>::First() const
{
	return m_pair.first;	
}

template <typename Key, typename Value>
Value& MyPair<Key, Value>::Second()
{
	return m_pair.second;
}

template <typename Key, typename Value>
const Value& MyPair<Key, Value>::Second() const
{
	return m_pair.second;	
}

}

#endif // MY_PAIR_H
