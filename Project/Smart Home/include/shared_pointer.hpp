#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include <cassert>
#include "atomic_value.hpp"
#include "Common.hpp"

namespace advcpp
{


template <typename T>
class SharedPointer
{
public:
    explicit SharedPointer(T * a_item = 0);
    SharedPointer(const SharedPointer & a_pointer);
    ~SharedPointer();
    SharedPointer & operator= (const SharedPointer & a_pointer);
    
    template <typename U>
    explicit SharedPointer(U * a_derived);

    template <typename U>
    SharedPointer(const SharedPointer<U> & a_pointer);


    T* operator ->(); 
    const T* operator ->() const; 
    T& operator *();
    const T& operator *() const; 
    
    void swap(SharedPointer & a_pointer);

    template <typename U>
    friend class SharedPointer;
    
    operator bool();

    
    
private:
    void copy(const SharedPointer & a_pointer);

    template <typename U>
    U operator()();

private:
    T * m_item;
public:    
    AtomicValue<int> * m_counter; 

};

template <typename T>
bool operator== (const SharedPointer<T>  a_first, const SharedPointer<T> a_second);

template <typename T>
bool operator!= (const SharedPointer<T>  a_first, const SharedPointer<T>  a_second);



} // namespace advcpp

#include "inl/shared_pointer.inl"

#endif // SHARED_POINTER_H