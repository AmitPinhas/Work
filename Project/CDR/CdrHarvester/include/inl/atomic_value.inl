#include <cassert>// assert

#include "common.hpp"// Uncopyable

namespace advcpp
{

template<typename T>
AtomicValue<T>::AtomicValue(T a_value)
:m_value(a_value)
{
    assert(sizeof(T) <= 8);
}

template<typename T>
void AtomicValue<T>::Set(T a_value)
{
    __sync_lock_test_and_set(&m_value, a_value);
}

template<typename T>
T AtomicValue<T>::Get() const
{
    return __sync_fetch_and_add(&m_value, 0);
}

template<typename T>
void AtomicValue<T>::operator+=(T a_num)
{
    __sync_fetch_and_add(&m_value, a_num);
}

template<typename T>
void AtomicValue<T>::operator-=(T a_num)
{
    __sync_fetch_and_sub(&m_value, a_num);
}

template<typename T>
void AtomicValue<T>::operator++()
{
    __sync_fetch_and_add(&m_value, 1);
}

template<typename T>
void AtomicValue<T>::operator--()
{
    __sync_fetch_and_sub(&m_value, 1);
}

AtomicFlag::AtomicFlag()
: m_flag( 0 )
{ 
}

inline bool AtomicFlag::SetIf(bool a_from, bool a_to)
{
    return __sync_bool_compare_and_swap(&m_flag, a_from, a_to);
}

inline bool AtomicFlag::Aquire()
{
    return SetIf(0, 1);
}

inline bool AtomicFlag::Release()
{
    return SetIf(1, 0);
}


}// advcpp namespace