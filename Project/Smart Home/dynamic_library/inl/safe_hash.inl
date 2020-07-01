
namespace advcpp
{

void DestroyMutex(Mutex & a_mutex)
{
    a_mutex.Destroy();
}

void LockMutex(Mutex & a_mutex)
{
    a_mutex.Lock();
}

void UnLockMutex(Mutex & a_mutex)
{
    a_mutex.UnLock();
}


template <typename Key, typename Value, typename HashFunc>
SafeHash<Key, Value, HashFunc>::SafeHash(size_t a_capacity, const HashFunc & a_hashFunc)
: m_table(a_capacity,a_hashFunc)
, m_mutexes(m_table.Capacity() / 6)
, m_cMutex(new Mutex[m_mutexes])
{
}

template <typename Key, typename Value, typename HashFunc>
SafeHash<Key, Value, HashFunc>::~SafeHash()
{
    destroyMutexes();
    delete[] m_cMutex;
}

template <typename Key, typename Value, typename HashFunc>
void SafeHash<Key, Value, HashFunc>::Insert(const Key & a_key, const Value & a_val)
{
    size_t index = m_table.HashIt(a_key);
    {
        Guard guard(m_cMutex[index % m_mutexes]);
        m_table.Insert(a_key, a_val);
    }
}


template <typename Key, typename Value, typename HashFunc>
template <typename Ch>
void SafeHash<Key, Value, HashFunc>::Upsert(const Key & a_key, Ch a_change)
{
    HashIterator<Key, Value> it = m_table.End();
    HashIterator<Key, Value> end = m_table.End();

    size_t index = m_table.HashIt(a_key);
    {
        Guard guard(m_cMutex[index % m_mutexes]);
        it = m_table.Find(a_key);
        if(end == it)
        {
            Value val;
            it = m_table.Insert(a_key, val);
        }
        a_change(it -> m_pair.m_value);
    }
}

template <typename Key, typename Value, typename HashFunc>
HashIterator<Key, Value> SafeHash<Key, Value, HashFunc>::find(const Key & a_key) 
{
    size_t index = m_table.HashIt(a_key);
    HashIterator<Key, Value> it = m_table.End();
    
    {
        Guard guard(m_cMutex[index % m_mutexes]);
        it = m_table.Find(a_key);
    }
    
    return it;
}

template <typename Key, typename Value, typename HashFunc>
const Value &  SafeHash<Key, Value, HashFunc>::Find(const Key & a_key) const
{
    size_t index = m_table.HashIt(a_key);
    HashIteratorConst<Key, Value> it = m_table.End();
    
    {
        Guard guard(m_cMutex[index % m_mutexes]);
        it = m_table.Find(a_key);
    }
    
    return (*it).m_pair.m_value;
}

template <typename Key, typename Value, typename HashFunc>
template <typename Ch>
bool SafeHash<Key, Value, HashFunc>::Change(const Key & a_key, Ch a_change)
{
    size_t index = m_table.HashIt(a_key);
    HashIterator<Key, Value> it = m_table.End();
    HashIterator<Key, Value> end = m_table.End();
    {
        Guard guard(m_cMutex[index % m_mutexes]);
        it = m_table.Find(a_key);
        if(it == end)
        {
            return false;
        }
        a_change(it -> m_pair.m_value);
        return true;
    }
}

template <typename Key, typename Value, typename HashFunc>
template <typename Ch>
void SafeHash<Key, Value, HashFunc>::ForEach(const Key & a_key, Ch a_change)
{
    lockdown();
    HashIterator<Key, Value> it = m_table.Begin();
    HashIterator<Key, Value> end = m_table.End();
    while(it != end)
    {
        a_change(it -> m_pair.m_value);
        ++it;
    }
    unlockDown();
}


template <typename Key, typename Value, typename HashFunc>
size_t SafeHash<Key, Value, HashFunc>::Capacity() const
{   
    return m_table.Capacity();
}


template <typename Key, typename Value, typename HashFunc>
size_t SafeHash<Key, Value, HashFunc>::Size() 
{   
    lockdown();
    size_t size = m_table.Size();
    unlockDown();
    return size;    
}

template <typename Key, typename Value, typename HashFunc>
size_t SafeHash<Key, Value, HashFunc>::LoadFactor() 
{   
    lockdown();
    size_t size = m_table.LoadFactor();
    unlockDown();
    return size;    
}

// template <typename Key, typename Value, typename HashFunc>
// bool SafeHash<Key, Value, HashFunc>::ReSize(size_t a_size)
// {
//     SafeHash<Key, Value, HashFunc> temp(a_size, m_hash);
// }


template <typename Key, typename Value, typename HashFunc>
void SafeHash<Key, Value, HashFunc>::swap(SafeHash & a_other)
{   
    std::swap(m_mutexes, a_other.m_mutexes);
	std::swap(m_cMutex, a_other.m_cMutex);
	Swap(m_table, a_other.m_table);
}

template <typename Key, typename Value, typename HashFunc>
void SafeHash<Key, Value, HashFunc>::destroyMutexes()
{
    std::for_each(m_cMutex, m_cMutex + m_mutexes, DestroyMutex);
}

template <typename Key, typename Value, typename HashFunc>
void SafeHash<Key, Value, HashFunc>::lockdown()
{
    std::for_each(m_cMutex, m_cMutex + m_mutexes, LockMutex);
}

template <typename Key, typename Value, typename HashFunc>
void SafeHash<Key, Value, HashFunc>::unlockDown()
{
    std::for_each(m_cMutex, m_cMutex + m_mutexes, UnLockMutex);
}


} // namespace advcpp
