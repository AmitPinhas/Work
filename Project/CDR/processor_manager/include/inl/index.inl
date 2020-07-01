#ifndef INDEX_INL
#define INDEX_INL

#include <cstddef>

namespace advcpp
{

template<typename Key, typename Value, typename Hasher>
Index<Key, Value, Hasher>::Index(size_t a_capacity, Hasher const& a_hasher)
: m_table(a_capacity, a_hasher)
{
}

template<typename Key, typename Value, typename Hasher>
template<typename Update>
void Index<Key, Value, Hasher>::Upsert(Key const& a_key ,Value const& a_val, Update a_update)
{
    m_table.Upsert(a_key, a_val, a_update);
}

template<typename Key, typename Value, typename Hasher>
bool Index<Key, Value, Hasher>::Find(Key const& a_key, Value& a_val) const
{
    return m_table.Find(a_key, a_val);
}


template<typename Key, typename Value, typename Hasher>
void Index<Key, Value, Hasher>::Drain(std::vector<Value>& a_clients)
{
    m_table.CopyAllTable(a_clients);
    m_table.Clear();
}

template<typename Key, typename Value, typename Hasher>
void Index<Key, Value, Hasher>::GetAll(std::vector<Value>& a_clients) const
{
    m_table.CopyAllTable(a_clients);
}



}//namespace advcpp


#endif //INDEX_INL