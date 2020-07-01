#ifndef DATA_STORAGE_INL
#define DATA_STORAGE_INL

namespace advcpp
{

template<typename Value, typename Key>
bool DataStorage::Find(DataStorage const& a_ds, std::vector<Value>& a_vec, Key const* a_key)
{
    if(0 == a_key)
    {
        return a_ds.GetAll(a_vec);
    }

    Value val;
    if(!a_ds.GetOne(*a_key, val))
    {
        return false;
    }
    a_vec.push_back(val);
    return true;

}

} //namespace advcpp


#endif