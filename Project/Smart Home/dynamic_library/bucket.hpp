#ifndef BUCKET_HPP
#define BUCKET_HPP
#include <list>
#include <utility>

namespace advcpp{

template <typename Key, typename Value>
class Bucket : private std::list<std::pair<Key, Value> >
{
public:
    typedef typename std::pair<Key, Value> Pair;
    typedef typename std::list<std::pair<Key, Value> >::iterator iterator;
    typedef typename std::list<std::pair<Key, Value> >::const_iterator const_iterator;

public:
    //Bucket();
    //Bucket(Bucket const& a_other) = default;
	//Bucket& operator=(Bucket const& a_rhs) = default;
	//~Bucket() = default;

	iterator Begin();
	iterator End();
	const_iterator Begin() const;
	const_iterator End() const;
	iterator Find(Key const& a_key);
	const_iterator Find(Key const& a_key) const;
	iterator Insert(Pair a_pair);
	iterator Remove(iterator a_position);
	
	size_t Size() const;
	bool IsEmpty() const;
	bool NotEmpty() const;
};

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator Bucket<Key, Value>::Begin()
{
    return this->begin();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator Bucket<Key, Value>::End()
{
    return this->end();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::const_iterator Bucket<Key, Value>::Begin() const
{
    return this->begin();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::const_iterator Bucket<Key, Value>::End() const
{
    return this->end();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator Bucket<Key, Value>::Find(Key const& a_key)
{
	
	typename Bucket<Key, Value>::iterator begin = Begin();
	typename Bucket<Key, Value>::iterator end = End();
	
	while(begin != end)
	{
		if (begin->first == a_key)
		{
			return begin;
		}
		++begin;
	}
	return end;
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::const_iterator Bucket<Key, Value>::Find(Key const& a_key) const
{
	typename Bucket<Key, Value>::iterator begin = Begin();
	typename Bucket<Key, Value>::iterator end = End();
	
	while(begin != end)
	{
		if (begin->first == a_key)
		{
			return begin;
		}
		++begin;
	}
	return end;
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator Bucket<Key, Value>::Insert(Pair a_pair)
{
    this->push_front(a_pair);
    return this->begin();
}

template <typename Key, typename Value>
typename Bucket<Key, Value>::iterator Bucket<Key, Value>::Remove(typename Bucket<Key, Value>::iterator a_position)
{
    return this->erase(a_position);
}

template <typename Key, typename Value>
size_t Bucket<Key, Value>::Size() const
{
	return this->size();
}

template <typename Key, typename Value>
bool Bucket<Key, Value>::IsEmpty() const
{
    return Size() == 0;
}

template <typename Key, typename Value>
bool Bucket<Key, Value>::NotEmpty() const
{
    return Size() > 0;
}

}//namespace advcpp
#endif //BUCKET_HPP
