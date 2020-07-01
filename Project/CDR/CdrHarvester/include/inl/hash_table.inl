

namespace advcpp
{

template <typename Key, typename Value, typename HashFunc>
HashTable<Key, Value, HashFunc>::HashTable(size_t a_capacity, size_t a_noThreads, HashFunc a_hashFunc)
:	std::vector<Bucket<Key, Value> >(myMath::GetNextPrime( a_capacity))
,	m_size(0)
,	m_capacity(myMath::GetNextPrime( a_capacity))
,	m_hashFunc(a_hashFunc)
{
	for (size_t i = 0; i < a_noThreads; i++)
	{
		m_keys.push_back( new Mutex() );
	}
}


template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::FindMutexIndex(size_t a_index) const NO_EXEPTION
{
	size_t noMutexes =  m_keys.size();

	size_t index = a_index / (m_capacity / noMutexes );
	if (index >= noMutexes)
	{
		return noMutexes - 1;
	}
	else
	{
		return index;
	}
}

template <typename Key, typename Value, typename HashFunc>
HashTable<Key, Value, HashFunc>::~HashTable() NO_EXEPTION
{
	size_t size = m_keys.size();

	for (size_t i = 0; i < size; i++)
	{
		delete m_keys[i];
	}
	
}


template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::FindIndex(Key const& a_key) const NO_EXEPTION
{
	return m_hashFunc(a_key) % m_capacity;
}


template <typename Key, typename Value, typename HashFunc>
Iterator<Key, Value> 
HashTable<Key, Value, HashFunc>::Insert(Key const& a_key, Value const& a_value)
{
	size_t index = FindIndex(a_key);
	Item<Key, Value> newItem(a_key, a_value, index);

	size_t mutexIndex = FindMutexIndex(index);

	{
		Guard mutex(*m_keys[mutexIndex]);
		Iterator<Key, Value> result = this-> at(index).Find(a_key, index);
		if (result == this-> at(index).End())
		{
			++m_size;
			return this-> at(index).PushBack(newItem);
		}
		return this-> at(m_capacity - 1).End();
	}
}


template <typename Key, typename Value, typename HashFunc>
Const_iterator<Key, Value> 
HashTable<Key, Value, HashFunc>::Find(Key const& a_key) const NO_EXEPTION
{
	size_t index = FindIndex(a_key);

	size_t mutexIndex = FindMutexIndex(index);

	{
		Guard mutex(*m_keys[mutexIndex]);

		Const_iterator<Key, Value> result = this-> at(index).Find(a_key, index);
		if (result == this-> at(index).End())
		{
			return this-> at(m_capacity - 1).End();
		}
		return result;
	}
}

template <typename Key, typename Value, typename HashFunc> 
Iterator<Key, Value>
HashTable<Key, Value, HashFunc>::Find(Key const& a_key) NO_EXEPTION
{
	size_t index = FindIndex(a_key);

	size_t mutexIndex = FindMutexIndex(index);

	{
		Guard mutex(*m_keys[mutexIndex]);
		Iterator<Key, Value> result = this-> at(index).Find(a_key, index);
		if (result == this-> at(index).End())
		{
			return this-> at(m_capacity - 1).End();
		}
		return result;
	}
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::Size() const NO_EXEPTION
{
	return m_size;
}

template <typename Key, typename Value, typename HashFunc>
size_t HashTable<Key, Value, HashFunc>::Capacity() const NO_EXEPTION
{
	return m_capacity;
}

template <typename Key, typename Value, typename HashFunc> 
double HashTable<Key, Value, HashFunc>::LoadFactor() const NO_EXEPTION
{
	return static_cast<double>(m_capacity) / m_size;
}


template <typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>:: Clear() NO_EXEPTION
{
	{
		Guard mutex(*m_keys[0]);
		typename std::vector< Bucket<Key, Value> >::iterator curr = this-> begin();
		typename std::vector< Bucket<Key, Value> >::iterator end = this-> end();
		while(curr != end)
		{
			curr-> Clear();
			++curr;
		}
		m_size = 0;
	}
}

template <typename Key, typename Value, typename HashFunc>
bool HashTable<Key, Value, HashFunc>::Remove(Key const& a_key, Value& a_value)
{
	size_t index = FindIndex(a_key);

	size_t mutexIndex = FindMutexIndex(index);

	{
		Guard mutex(*m_keys[mutexIndex]);
		if (this-> at(index).Remove(a_key, a_value, index) )
		{
			--m_size;
			return true;
		}
	}
	return false;
}
template <typename Key, typename Value, typename HashFunc>
Value& HashTable<Key, Value, HashFunc>::operator[](Key const& a_key) NO_EXEPTION
{
	size_t index = FindIndex(a_key);

	size_t mutexIndex = FindMutexIndex(index);

	{
		Guard mutex(*m_keys[mutexIndex]);
		Iterator<Key, Value> result = this-> at(index).Find(a_key, index);
		if (result == this-> at(index).End())
		{
			Item<Key, Value> newItem(a_key, Value (), index);
			++m_size;
			return ( *(this-> at(index).PushBack(newItem)) ) .second;
		}
		else
		{
			return (*result).second;
		}
	}
}

template <typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::ReSize(size_t a_newCap)
{
	HashTable<Key, Value, HashFunc> temp(a_newCap, m_keys.size(), m_hashFunc);
	for(size_t i = 0 ; i < m_capacity ; ++i)
	{
		while (! this-> at( i ).IsEmpty())
		{
			Iterator<Key, Value> curr = this-> at( i ).GetFirst();
			temp.Insert((*curr).first, (*curr).second);
			this-> at( i ).PopHead();
		} 
	}
	this-> Swap(temp);
}


template <typename Key, typename Value, typename HashFunc>
void HashTable<Key, Value, HashFunc>::Swap(HashTable<Key, Value, HashFunc>& a_lhs) NO_EXEPTION
{
	{
		Guard mutex(*m_keys[0]);
		std::swap(m_capacity, a_lhs.m_capacity);
		std::swap(m_size, a_lhs.m_size);
		std::vector< Bucket<Key, Value> >::swap(a_lhs);
	}
}

template <typename Key, typename Value, typename HashFunc>
void Swap(HashTable<Key, Value, HashFunc>& a_rhs, HashTable<Key, Value, HashFunc>& a_lhs) NO_EXEPTION
{
	a_rhs.Swap(a_lhs);
}

template <typename Key, typename Value, typename HashFunc>
template<typename Functor>
void HashTable<Key, Value, HashFunc>::ForEach(Functor a_func)
{
	const size_t vecSize = std::vector< Bucket<Key, Value> >::size();

	for (size_t i = 0; i < vecSize; ++i)
	{
		size_t mutexIndex = FindMutexIndex(i);
		Guard mutex(*m_keys[mutexIndex]);
		this-> at( i ).ForEach(a_func);
	}
}


}//namespace