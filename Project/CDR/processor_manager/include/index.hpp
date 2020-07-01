#ifndef INDEX_CLIENTS_HPP
#define INDEX_CLIENTS_HPP

#include "concurrent_hash_table.hpp"

namespace advcpp
{

template<typename Key, typename Value, typename Hasher>
class Index
{
public:
    Index(size_t a_capacity, Hasher const& a_hasher);

    template<typename Update>
    void Upsert(Key const& a_key ,Value const& a_val, Update a_update);

    bool Find(Key const& a_key, Value& a_val) const;
    void GetAll(std::vector<Value>& a_clients) const;

    void Drain(std::vector<Value>& a_clients);
    

private:
    ConcurrentHashTable<const Key, Value, Hasher> m_table;    
};

} //namespace advcpp

#include "index.inl"

#endif //INDEX_CLIENTS_HPP