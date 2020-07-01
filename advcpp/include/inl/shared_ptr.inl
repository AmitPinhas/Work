#ifndef SHARED_PTR_INL
#define SHARED_PTR_INL

#include <cassert>

namespace advcpp
{
template <typename T> 
SharedPtr<T>::SharedPtr(T* a_ptr)
: m_ptr(a_ptr)
, m_refCount(new AtomicValue<size_t>())
{
    if(a_ptr)
    {
        ++*m_refCount;
    }
}

template <typename T> 
SharedPtr<T>::SharedPtr(const SharedPtr& a_rhs)
{
    copy(a_rhs);
}

template <typename T> 
template <typename Derive> 
SharedPtr<T>::SharedPtr(const SharedPtr<Derive>& a_rhs)
: m_ptr(a_rhs.m_ptr)
, m_refCount(a_rhs.m_refCount)
{
    if(m_ptr)
    {
        ++*m_refCount;
    }   
}

template <typename T> 
SharedPtr<T>::~SharedPtr() NOEXCEPT
{
    remove();
}

template <typename T> 
SharedPtr<T>& SharedPtr<T>::operator = (const SharedPtr& a_rhs)
{
    remove();
    copy(a_rhs);
    return *this;    
}

template <typename T> 
template <typename Derive> 
SharedPtr<T>& SharedPtr<T>::operator = (const SharedPtr<Derive>& a_rhs)
{  
    remove();
    copy(a_rhs);
    return *this;    
} 

template <typename T> 
T* SharedPtr<T>::operator -> ()
{
    return const_cast<T*>(static_cast<SharedPtr<T> const &>(*this).operator->());    
}

template <typename T> 
const T* SharedPtr<T>::operator -> () const
{
    return ptr();
}

template <typename T> 
T& SharedPtr<T>::operator * ()
{
    return const_cast<T&>(static_cast<SharedPtr<T> const &>(*this).operator*()); 
}

template <typename T> 
const T& SharedPtr<T>::operator * () const
{
    return *ptr();
}

template <typename T> 
bool SharedPtr<T>::IsEqual(const SharedPtr& a_rhs) const
{
    return ptr() == a_rhs.ptr();
}

template <typename T> 
bool SharedPtr<T>::IsEqual(int a_rhs) const
{
    return ptr() == a_rhs;    
}

template <typename T>
bool SharedPtr<T>::operator ! ()
{
    return !ptr();
}

template <typename T> 
AtomicValue<size_t>* SharedPtr<T>::allocCounter()
{
    return new AtomicValue<size_t>(1);
}

template <typename T> 
T* SharedPtr<T>::ptr()
{
    return const_cast<T*>(static_cast<SharedPtr<T> const &>(*this).ptr());      
}

template <typename T> 
const T* SharedPtr<T>::ptr() const
{
    return m_ptr;
}

template <typename T> 
AtomicValue<size_t>* SharedPtr<T>::ptrCounter()
{
    return const_cast<AtomicValue<size_t>*>(static_cast<SharedPtr<T> const &>(*this).ptrCounter());   
}

template <typename T> 
const AtomicValue<size_t>* SharedPtr<T>::ptrCounter() const
{
    return m_refCount;
}

template <typename T> 
void SharedPtr<T>::copy(const SharedPtr& a_rhs)
{
    m_ptr = a_rhs.m_ptr;
    m_refCount = a_rhs.m_refCount;
    ++*m_refCount;    
}

template <typename T> 
template <typename Derive>     
void SharedPtr<T>::copy(const SharedPtr<Derive>& a_rhs)
{
    m_ptr = a_rhs.m_ptr;
    m_refCount = a_rhs.m_refCount;
    ++*m_refCount;    
}

template <typename T> 
AtomicValue<size_t>& SharedPtr<T>::counter()
{
    return const_cast<AtomicValue<size_t>&>(static_cast<SharedPtr<T> const &>(*this).counter());
}

template <typename T> 
const AtomicValue<size_t>& SharedPtr<T>::counter() const
{
    return *m_refCount;    
}

template <typename T> 
void SharedPtr<T>::remove()
{
    if(counter().Get() > 1)
    {
        --counter();
        return;
    }
    
    if(m_ptr)
    {
        delete m_ptr;        
    }

    delete m_refCount;    
}

template <typename T>    
bool operator ==(const SharedPtr<T>& a_lhs, const SharedPtr<T>& a_rhs)
{
    return a_lhs.IsEqual(a_rhs);
}

template <typename T>    
bool operator ==(const SharedPtr<T>& a_lhs, int a_rhs)
{
    return a_lhs.IsEqual(a_rhs);    
}

template <typename T>    
bool operator ==(int a_lhs, const SharedPtr<T>& a_rhs)
{
    return a_rhs.IsEqual(a_lhs);        
}

template <typename T>    
bool operator !=(const SharedPtr<T>& a_lhs, const SharedPtr<T>& a_rhs)
{
    return !(a_lhs == a_rhs);
}

template <typename T>    
bool operator !=(const SharedPtr<T>& a_lhs, int a_rhs)
{
    return !(a_lhs == a_rhs);    
}

template <typename T>    
bool operator !=(int a_lhs, const SharedPtr<T>& a_rhs)
{
    return !(a_lhs == a_rhs);       
}
} // namespace advcpp

#endif // SHARED_PTR_INL