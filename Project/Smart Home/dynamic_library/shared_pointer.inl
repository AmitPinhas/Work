#include "shared_pointer.hpp"
#include <algorithm> // swap

namespace advcpp
{

template <typename T>
SharedPointer<T>::SharedPointer(T * a_item)
: m_item(a_item)
, m_counter(new AtomicValue<int>(0))
{  
    if (m_item)
    {
        ++*m_counter;
    }
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer & a_pointer)
: m_item(a_pointer.m_item)
, m_counter(a_pointer.m_counter)
{
    ++(*m_counter);
}

template <typename T>
template <typename U>
SharedPointer<T>::SharedPointer(const SharedPointer<U> & a_pointer)
: m_item(a_pointer.m_item)
, m_counter(a_pointer.m_counter)
{
    ++(*m_counter);
}

template <typename T>
SharedPointer<T>::~SharedPointer()
{
    if(m_counter -> Value() <= 1)
    {
        if(m_item)
        {
            delete m_item;
        }
        
        delete m_counter;
        
        return;
    }
    --*m_counter;    
}


template <typename T>
SharedPointer<T> & SharedPointer<T>::operator= (const SharedPointer & a_pointer)
{    
    copy(a_pointer);
    //++(*m_counter);
    return *this;
}

template <typename T>
void SharedPointer<T>::copy(const SharedPointer & a_pointer)
{
    SharedPointer temp(a_pointer);
    swap(temp);
}

template <typename T>
void SharedPointer<T>::swap(SharedPointer & a_pointer)
{
    std::swap(m_item, a_pointer.m_item);
    std::swap(m_counter, a_pointer.m_counter);
}

template <typename T>
const T* SharedPointer<T>::operator ->() const
{
    return m_item;
}

template <typename T>
T* SharedPointer<T>::operator ->() 
{
    return const_cast<T *> (static_cast<SharedPointer<T>const &>(*this).operator -> ());
}

template <typename T>
const T& SharedPointer<T>::operator *() const
{
    return *m_item;
}

template <typename T>
T& SharedPointer<T>::operator *()
{
    return const_cast<T &> (static_cast<SharedPointer<T>const &>(*this).operator*());
}

template <typename T>
SharedPointer<T>::operator bool()
{
    return m_item;
}

template <typename T>
template <typename U>
SharedPointer<T>::SharedPointer(U * a_derived)
: m_item(a_derived)
, m_counter(new AtomicValue<int>(0))
{
    if(a_derived)
    {
        ++*m_counter;
    }
}

template <typename T>
bool operator== (const SharedPointer<T>  a_first, const SharedPointer<T>  a_second)
{
    return &(*a_first) == &(*a_second);
}

template <typename T>
bool operator!= (const SharedPointer<T>  a_first, const SharedPointer<T>  a_second)
{
    return &(*a_first) != &(*a_second);
}



} // namespace advcpp
