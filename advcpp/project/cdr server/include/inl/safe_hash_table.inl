#include <algorithm> // std::algorithm

namespace advcpp
{
template < typename Key, typename Value, typename HashFunc>
SafeHashTable<Key, Value, HashFunc>::SafeHashTable(size_t a_capacity, const HashFunc& a_hashFunc, size_t a_numThreads) 
: m_safeHash(a_capacity, a_hashFunc)
, m_capacityMutexes(a_numThreads)
, m_mutexes(a_numThreads)
, m_hashFunc(a_hashFunc)
{
}   

template < typename Key, typename Value, typename HashFunc>
MyIter<Key, Value> SafeHashTable<Key, Value, HashFunc>::Insert(const Key& a_key, const Value& a_value)
{
    size_t indexMutex = m_hashFunc(a_key) % m_capacityMutexes;
    MyIter<Key, Value> iter;

    {
        Guard guard(m_mutexes[indexMutex]);

        iter = m_safeHash.Insert(a_key, a_value);
    }
    return iter;

}

template < typename Key, typename Value, typename HashFunc>
MyIterConst<Key, Value> SafeHashTable<Key, Value, HashFunc>::Find(const Key& a_key) const
{
    size_t indexMutex = m_hashFunc(a_key) % m_capacityMutexes;
    MyIterConst<Key, Value> iter;

    {
        Guard guard(m_mutexes[indexMutex]);    

        iter = m_safeHash.Find(a_key);
    }

    return iter;
}

template < typename Key, typename Value, typename HashFunc>
MyIter<Key, Value> SafeHashTable<Key, Value, HashFunc>::Find(const Key& a_key)
{
    size_t indexMutex = m_hashFunc(a_key) % m_capacityMutexes;
    MyIter<Key, Value> iter;

    {
        Guard guard(m_mutexes[indexMutex]);    

        iter = m_safeHash.Find(a_key);
    }

    return iter;
}

template < typename Key, typename Value, typename HashFunc>
bool SafeHashTable<Key, Value, HashFunc>::Remove(const Key& a_key, Value& a_value)
{
    size_t indexMutex = m_hashFunc(a_key) % m_capacityMutexes;
    bool result;
    
    {
        Guard guard(m_mutexes[indexMutex]);  

        result = m_safeHash.Rmove(a_key, a_value);
    }

    return result;
}

template < typename Key, typename Value, typename HashFunc>
Value SafeHashTable<Key, Value, HashFunc>::operator[](const Key& a_key)
{
    size_t indexMutex = m_hashFunc(a_key) % m_capacityMutexes;
    Value result;
    
    {
        Guard guard(m_mutexes[indexMutex]);      

        result = m_safeHash[a_key];
    }

    return result;
}

template < typename Key, typename Value, typename HashFunc>
MyIter<Key, Value> SafeHashTable<Key, Value, HashFunc>::Begin()
{
    lockAll();

    MyIter<Key, Value> result = m_safeHash.Begin();    

    unlockAll();    

    return result; 
}

template < typename Key, typename Value, typename HashFunc>
typename SafeHashTable<Key, Value, HashFunc>::const_iterator SafeHashTable<Key, Value, HashFunc>::Begin() const
{
    lockAll();

    const_iterator result = m_safeHash.Begin();    

    unlockAll();    

    return result;     
}

template < typename Key, typename Value, typename HashFunc>
MyIter<Key, Value> SafeHashTable<Key, Value, HashFunc>::End()
{
    lockAll();

    MyIter<Key, Value> result = m_safeHash.End();    

    unlockAll();    

    return result;         
}

template < typename Key, typename Value, typename HashFunc>
typename SafeHashTable<Key, Value, HashFunc>::const_iterator SafeHashTable<Key, Value, HashFunc>::End() const
{
    lockAll();

    const_iterator result = m_safeHash.End();    

    unlockAll();    

    return result;      
}

template < typename Key, typename Value, typename HashFunc>
size_t SafeHashTable<Key, Value, HashFunc>::Size() const
{
    lockAll();

    size_t result = m_safeHash.Size();    

    unlockAll();    

    return result;
}

template < typename Key, typename Value, typename HashFunc>
size_t SafeHashTable<Key, Value, HashFunc>::Capacity() const
{
    lockAll();

    size_t result = m_safeHash.Capacity();    

    unlockAll();    

    return result;     
}

template < typename Key, typename Value, typename HashFunc>
double SafeHashTable<Key, Value, HashFunc>::LoadFactor() const
{   
    lockAll();

    double result = m_safeHash.LoadFactor();    

    unlockAll();    

    return result; 
}

template < typename Key, typename Value, typename HashFunc>
void SafeHashTable<Key, Value, HashFunc>::Clear()
{
    lockAll();

    m_safeHash.Clear();  

    unlockAll();           
}

template < typename Key, typename Value, typename HashFunc>
void SafeHashTable<Key, Value, HashFunc>::Resize(size_t a_capacity)
{
    lockAll();

    m_safeHash.Resize(a_capacity);   

    unlockAll();   
}

template < typename Key, typename Value, typename HashFunc>	
void SafeHashTable<Key, Value, HashFunc>::Swap(HashTable<Key, Value, HashFunc>& a_hash)
{
    lockAll();

    m_safeHash.Swap(a_hash);

    unlockAll();      
}

template < typename Key, typename Value, typename HashFunc>	
void SafeHashTable<Key, Value, HashFunc>::lockAll()
{
    std::vector<Mutex>::iterator begin = m_mutexes.begin();
    std::vector<Mutex>::iterator end = m_mutexes.end();

    std::for_each(begin, end, lockMutex);   
}

template < typename Key, typename Value, typename HashFunc>	
void SafeHashTable<Key, Value, HashFunc>::unlockAll()
{
    std::vector<Mutex>::iterator begin = m_mutexes.begin();
    std::vector<Mutex>::iterator end = m_mutexes.end();

    std::for_each(begin, end, unlockMutex);   
}

template < typename Key, typename Value, typename HashFunc>	
void SafeHashTable<Key, Value, HashFunc>::lockMutex(Mutex a_mutex)
{
    a_mutex.Lock();
}

template < typename Key, typename Value, typename HashFunc>	
void SafeHashTable<Key, Value, HashFunc>::unlockMutex(Mutex a_mutex)
{
    a_mutex.UnLock();
}
} // namespace advcpp