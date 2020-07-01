#ifndef ATOMIC_VALUE_HPP
#define ATOMIC_VALUE_HPP
#include <cassert>// assert

#include "common.hpp"// Uncopyable


namespace advcpp
{


template<typename T>
class AtomicValue: public UnCopyAble
{
public:
    explicit AtomicValue(T a_value = 0);  
    //~AtomicValue(); default

    void Set(T a_value = 0);
    T Get() const;

    void operator+=(T a_num);
    void operator-=(T a_num);

    void operator++();
    void operator--();

private:
    T m_value;
};


class AtomicFlag : public UnCopyAble
{
public:
    AtomicFlag();
    //~AtomicFlag(); deafult

    bool SetIf(bool a_from, bool a_to);
    bool Aquire();
    bool Release();

private:
    int m_flag;
};

}//advcpp namespace
#include "inl/atomic_value.inl"
#endif//ATOMIC_VALUE_HPP