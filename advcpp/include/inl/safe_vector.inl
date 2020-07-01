#ifndef SAFE_VECTOR_INL
#define SAFE_VECTOR_INL

#include <cstddef> // size_t

namespace advcpp
{

template <typename T>
void SafeVector<T>::Reserve(size_t a_num)
{
    Guard locker(m_mutex);
    m_vector.reserve(a_num);
}

template <typename T>
size_t SafeVector<T>::Size() const
{
    Guard locker(m_mutex);
    return m_vector.size();
}

template <typename T>
T& SafeVector<T>::Back()
{
    return const_cast<T&>(static_cast<const SafeVector&>(*this).Back());       
}

template <typename T>
const T& SafeVector<T>::Back() const
{
    Guard locker(m_mutex);
    return m_vector.back();       
}

template <typename T>
void SafeVector<T>::PopBack()
{
    Guard locker(m_mutex);
    return m_vector.pop_back();    
}

template <typename T>
void SafeVector<T>::PushBack(const T& a_val)
{
    Guard locker(m_mutex);
    return m_vector.push_back(a_val);      
}

} // namespace advcpp

#endif // SAFE_VECTOR_INL