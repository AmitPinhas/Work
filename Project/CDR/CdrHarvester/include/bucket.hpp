#ifndef BACKET_HPP
#define BACKET_HPP

#include <cstdlib>

namespace advcpp
{
    

template <typename Key, typename Value>
struct Item
{
	Item(Key a_key, Value a_value, size_t a_hv);

	size_t m_hv;
	std::pair<Key, Value> m_pair;
};


template <typename Key>
class Hasher
{
public:
	size_t operator()(Key a_key);
};




template <typename Key, typename Value>
class Iterator
{
public:
	Iterator(typename std::list<Item<Key, Value> >::iterator a_iter);
	

	Iterator operator--();
	Iterator operator++();

	std::pair<Key, Value>& operator*();
	std::pair<Key, Value>& operator->();

	bool IsEqual(Iterator<Key, Value> const& a_lhs) const;

private:
	typename std::list<Item<Key, Value> >::iterator m_iter;
};


template <typename Key, typename Value>
class Const_iterator
{
public:
	Const_iterator(typename std::list<Item<Key, Value> >::const_iterator a_iter);

	Const_iterator<Key, Value> operator--();
	Const_iterator<Key, Value> operator++();
	
	std::pair<Key, Value> const& operator*();
	std::pair<Key, Value> const& operator->();	

	bool IsEqual(Const_iterator<Key, Value> const& a_lhs) const;

private:
	typename std::list<Item<Key, Value> >::const_iterator m_iter;
};

template <typename Key, typename Value>
class Bucket
{
public:
	//Bucket(); default
	//~Bucket(); default
	//const Backet& Backet(const Backet& a_lhs); default
	//const Backet& operator=(const Backet& a_lhs); default 

	Iterator<Key, Value> PushBack(Item<Key, Value> const & a_item);

	Iterator<Key, Value> Find(Key const& a_key, size_t a_hv);
	Const_iterator<Key, Value> Find(Key const& a_key, size_t a_hv) const;

	std::pair<Key, Value>const& At(size_t a_index) const ;
	
	void Clear();

	bool Remove(Key const& a_key, Value& a_value, size_t a_hv);

	void PopHead();
	Iterator<Key, Value> GetFirst();
	bool IsEmpty() const; 

	Iterator<Key, Value> Begin();
	Const_iterator<Key, Value> Begin() const ;

	Iterator<Key, Value> End();
	Const_iterator<Key, Value> End() const;

	template<typename Functor>
	void ForEach(Functor a_func);
	
private:
	std::list<Item<Key, Value> > m_list;
};


template <typename iter, typename Key>
iter Search(iter a_curr, iter a_end, Key a_key, size_t a_hv)
{
	while (a_curr != a_end) 
	{
		if(a_hv != a_curr-> m_hv)
		{
			continue;
		}
		if (a_key == a_curr-> m_pair.first)
		{
			return a_curr;
		}
	++a_curr;
	}
	return a_end;
}



////////////////////////iter funcs


template <typename Key, typename Value>
Iterator<Key, Value>::Iterator(typename std::list<Item<Key, Value> >::iterator a_iter)
:	m_iter(a_iter)
{
}

template <typename Key, typename Value>
Iterator<Key, Value> Iterator<Key, Value>::operator--()
{
	--m_iter;
	return *this;
}

template <typename Key, typename Value>
Iterator<Key, Value> Iterator<Key, Value>::operator++()
{
	++m_iter;
	return *this;
}

template <typename Key, typename Value>
std::pair<Key, Value>& Iterator<Key, Value>::operator*()
{
	return (*m_iter).m_pair;
}

template <typename Key, typename Value>
std::pair<Key, Value>& Iterator<Key, Value>::operator->()
{
	return (*m_iter).m_pair;
}

template <typename Key, typename Value>
bool Iterator<Key, Value>::IsEqual(Iterator<Key, Value> const& a_lhs) const
{
	return m_iter == a_lhs.m_iter;
}

template <typename Key, typename Value>
bool operator==(Iterator<Key, Value> const& a_lhs, Iterator<Key, Value> const& a_rhs)
{
	return a_lhs.IsEqual(a_rhs);
}


template <typename Key, typename Value>
bool operator!=(Iterator<Key, Value> const& a_lhs, Iterator<Key, Value> const& a_rhs)
{
	return !a_lhs.IsEqual(a_rhs);
}

///////////////////////////// const  Iterator 

template <typename Key, typename Value>
Const_iterator<Key, Value>::Const_iterator(typename std::list<Item<Key, Value> >::const_iterator a_iter)
:	m_iter(a_iter)
{
}


template <typename Key, typename Value>
Const_iterator<Key, Value> Const_iterator<Key, Value>::operator--()
{
	--m_iter;
	return *this;
}

template <typename Key, typename Value>
Const_iterator<Key, Value> Const_iterator<Key, Value>::operator++()
{
	++m_iter;
	return *this;
}

template <typename Key, typename Value>
std::pair<Key, Value>const& Const_iterator<Key, Value>::operator*()
{
	return (*m_iter).m_pair;
}

template <typename Key, typename Value>
std::pair<Key, Value>const& Const_iterator<Key, Value>::operator->()
{
	return (*m_iter).m_pair;
}


template <typename Key, typename Value>
bool Const_iterator<Key, Value>::IsEqual(Const_iterator<Key, Value> const& a_lhs) const
{
	return m_iter == a_lhs.m_iter;
}

template <typename Key, typename Value>
bool operator==(Const_iterator<Key, Value> const& a_lhs, Const_iterator<Key, Value> const& a_rhs)
{
	return a_lhs.IsEqual(a_rhs);
}


template <typename Key, typename Value>
bool operator!=(Const_iterator<Key, Value> const& a_lhs, Const_iterator<Key, Value> const& a_rhs)
{
	return !a_lhs.IsEqual(a_rhs);
}


///////////////////////////////////funcs
template <typename Key, typename Value>
template<typename Functor>
void Bucket<Key, Value>::ForEach(Functor a_func)
{
	typename std::list<Item<Key, Value> >::iterator curr = m_list.begin();
	typename std::list<Item<Key, Value> >::iterator end = m_list.end();

	while(curr != end)
	{
		a_func( curr->m_pair.second ); 
		++curr;
	}
}

template <typename Key, typename Value>
Iterator<Key, Value> Bucket<Key, Value>::PushBack(Item<Key, Value> const & a_item)
{
	return m_list.insert(m_list.end(), a_item);
}

template <typename Key, typename Value>
Iterator<Key, Value> 
Bucket<Key, Value>::Find(Key const& a_key, size_t a_hv)
{
	return Search(m_list.begin(), m_list.end(), a_key, a_hv);
}

template <typename Key, typename Value>
Const_iterator<Key, Value> 
Bucket<Key, Value>::Find(Key const& a_key, size_t a_hv) const
{
	return Search(m_list.begin(), m_list.end(), a_key, a_hv);
}



template <typename Key, typename Value>
Iterator<Key, Value> Bucket<Key, Value>::Begin()
{
	return m_list.begin();	
}



template <typename Key, typename Value>
Iterator<Key, Value> Bucket<Key, Value>::End()
{
	Iterator<Key, Value> temp = m_list.end();
	return temp;
}



template <typename Key, typename Value>
Const_iterator<Key, Value> Bucket<Key, Value>::Begin() const
{
	Const_iterator<Key, Value> temp = m_list.begin() ;
	return temp;
}



template <typename Key, typename Value>
Const_iterator<Key, Value> Bucket<Key, Value>::End() const
{
	Const_iterator<Key, Value> temp(m_list.end() );
	return temp;
}



template <typename Key, typename Value>
void  Bucket<Key, Value>::Clear()
{
	m_list.clear();
}




template <typename Key, typename Value>
bool Bucket<Key, Value>::Remove(Key const& a_key, Value& a_value, size_t a_hv)
{
	typename std::list<Item<Key, Value> >::iterator result = Search(m_list.begin(), m_list.end(), a_key, a_hv);
	if (result != m_list.end())
	{
		a_value = (*result).m_pair.second;
		m_list.erase(result);
		return true;
	}
	return false;
}




template <typename Key, typename Value>
void Bucket<Key, Value>::PopHead()
{
	m_list.pop_front();
}



template <typename Key, typename Value>
Iterator<Key, Value> Bucket<Key, Value>::GetFirst()
{
	Iterator<Key, Value> temp = m_list.begin();
	return temp;
}



template <typename Key, typename Value>
bool Bucket<Key, Value>::IsEmpty() const
{
	return m_list.empty();
}

template <typename Key, typename Value>
Item<Key, Value>::Item(Key a_key, Value a_value, size_t a_hv)
:	m_hv(a_hv)
,	m_pair(a_key, a_value)
{
}
////////////////////////////hash deafult funcs

template<typename Key>
size_t Hasher<Key>::operator()(Key a_key)
{
	return Hash(a_key);
}


size_t Hash(int a_key)
{
	return a_key;
}

size_t Hash(double a_key)
{
	return a_key;
}

size_t Hash(char a_key)
{
	return a_key;
}

template<typename T>
size_t Hash(T a_key)
{
	return hash(a_key);
}





 

}// end advcpp namespace

#endif // BUCKET_HPP
