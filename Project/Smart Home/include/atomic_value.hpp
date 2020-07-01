#ifndef ATOMIC_H
#define ATOMIC_H

#include "Common.hpp"

namespace advcpp
{

template <typename T> 
class AtomicValue : private UnCopyable
{
public: 
    AtomicValue(T a_arg = 0) NOEXCEPTION;
    //~AtomicValue(); = default;

    T Value() const NOEXCEPTION;
    void Set(T a_arg = 0) NOEXCEPTION;
    T Get() const NOEXCEPTION;

    void operator += (T a_arg) NOEXCEPTION;
    void operator -= (T a_arg) NOEXCEPTION;

    void operator ++ () NOEXCEPTION;
    void operator -- () NOEXCEPTION;

private: 
    T m_value;

};

template <> 
class AtomicValue<bool>
{
public:
    AtomicValue(bool a_value = 0) NOEXCEPTION;
    // ~AtomicValue(); = default

    bool SetIf(bool a, bool b) NOEXCEPTION;

    bool Acquire() NOEXCEPTION;
    void Release() NOEXCEPTION;

private:
    int m_flag;

};

typedef AtomicValue<bool> AtomicFlag;

} // namespace advcpp

#include "inl/atomic_value.inl"
#endif // ATOMIC_H
