#ifndef ATOMIC_H
#define ATOMIC_H
#include "common.hpp"

namespace advcpp
{

template <typename T>
class AtomicValue : private Uncopyable
{
public:
    explicit AtomicValue(T a_num = 0);
    // rule 3 = default;

    void operator+=(T a_num);
    void operator-=(T a_num);
    void operator++();
    void operator--();

    void Set(T a_num);
    T Get() const;
    T Value() const;

    operator size_t() const{ return Get(); }
    operator int() const { return Get(); }    

private:
    mutable T m_num;
};

typedef AtomicValue<bool> AtomicFlag;

template<>
class AtomicValue<bool>
{
public:
    bool Acquire();
    void Release();

private:
    int m_num;    
};


}//namespace advcpp

#include "inl/atomic.inl"

#endif //ATOMIC_H
