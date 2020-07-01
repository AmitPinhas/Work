#ifndef ATOMIC_INL
#define ATOMIC_INL

namespace advcpp{

template <typename T>
AtomicValue<T>::AtomicValue(T a_num)
: m_num(a_num)
{
}

template <typename T>
void AtomicValue<T>::operator+=(T a_num)
{
    __sync_fetch_and_add (&m_num, a_num);
}

template <typename T>
void AtomicValue<T>::operator-=(T a_num)
{
    __sync_fetch_and_sub (&m_num, a_num);
}

template <typename T>
void AtomicValue<T>::operator++()
{
     __sync_fetch_and_add (&m_num, 1);
}

template <typename T>
void AtomicValue<T>::operator--()
{
   __sync_fetch_and_sub (&m_num, 1);
}

template <typename T>
void AtomicValue<T>::Set(T a_num)
{
    __sync_lock_test_and_set(&m_num, a_num);    
}

template <typename T>
T AtomicValue<T>::Get() const
{
    return __sync_fetch_and_add(&m_num, T(0));
}

template <typename T>
T AtomicValue<T>::Value() const 
{
    return __sync_fetch_and_add(&m_num, T(0));
}

/*
template<>
bool AtomicValue<bool>::Acquire()
{
    return __sync_lock_test_and_set(&m_num, 0);
}

template<>
void AtomicValue<bool>::Release()
{
    __sync_lock_release (&m_num);
}
*/


} //namespace advcpp
#endif //ATOMIC_INL