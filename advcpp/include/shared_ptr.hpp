#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>    // size_t
#include "common.hpp"
#include "atomic_value.hpp"

namespace advcpp
{
    
template <typename T>    
class SharedPtr
{
public:
    explicit SharedPtr(T* a_ptr = 0);
    SharedPtr(const SharedPtr& a_rhs);

    template <typename Derive> 
    SharedPtr(const SharedPtr<Derive>& a_rhs);

    ~SharedPtr() NOEXCEPT;

    SharedPtr& operator = (const SharedPtr& a_rhs);
    
    template <typename Derive> 
    SharedPtr& operator = (const SharedPtr<Derive>& a_rhs);    

    T* operator -> ();
    const T* operator -> () const;  

    T& operator * ();
    const T& operator * () const;

    bool IsEqual(const SharedPtr& a_rhs) const; 
    bool IsEqual(int a_rhs) const;  

    bool operator ! (); 

    template <typename Derive>
    friend class SharedPtr;

private:
    AtomicValue<size_t>* allocCounter();

    T* ptr();
    const T* ptr() const;

    AtomicValue<size_t>* ptrCounter();
    const AtomicValue<size_t>* ptrCounter() const;

    AtomicValue<size_t>& counter();
    const AtomicValue<size_t>& counter() const;  

    void copy(const SharedPtr& a_rhs);

    template <typename Derive>     
    void copy(const SharedPtr<Derive>& a_rhs);

    void remove();

private:
    T* m_ptr;
    AtomicValue<size_t>* m_refCount;
};

template <typename T>    
bool operator ==(const SharedPtr<T>& a_lhs, const SharedPtr<T>& a_rhs);

template <typename T>    
bool operator ==(const SharedPtr<T>& a_lhs, int a_rhs);

template <typename T>    
bool operator ==(int a_lhs, const SharedPtr<T>& a_rhs);

template <typename T>    
bool operator !=(const SharedPtr<T>& a_lhs, const SharedPtr<T>& a_rhs);

template <typename T>    
bool operator !=(const SharedPtr<T>& a_lhs, int a_rhs);

template <typename T>    
bool operator !=(int a_lhs, const SharedPtr<T>& a_rhs);
} // namespace advcpp

#include "shared_ptr.inl"

#endif // SHARED_PTR_HPP
