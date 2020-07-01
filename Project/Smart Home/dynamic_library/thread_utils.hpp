#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

#include <vector> // using vectors
#include <algorithm> // generate for_each
#include <unistd.h> //  sysconf(_SC_NPROCESSORS_ONLN)
#include "thread.hpp" // threads
#include "Common.hpp" // exception throws 
#include "mutex.hpp" // mutex
#include "counter.hpp" // Count objfunc

namespace advcpp
{

template <typename T , typename Generator>
class VectorFill : public IRunnable
{
public:
    typedef typename std::vector<T>::iterator iterator;

    VectorFill(iterator begin, iterator end, Generator & a_generator) NOEXCEPTION;

    virtual void Run() NOEXCEPTION;

private:
    iterator m_begin;
    iterator m_end;
    Generator & m_generator;
};

template <typename C>
class ContainerSum : public IRunnable
{
public:
    typedef typename C::const_iterator iterator;

    ContainerSum(iterator begin, iterator end) NOEXCEPTION;

    virtual void Run() NOEXCEPTION;

    double Value() const NOEXCEPTION;

private:
    iterator m_begin;
    iterator m_end;
    double m_result;

};

template <typename C>
class ContainerMul : public IRunnable
{
public:
    typedef typename C::const_iterator iterator;

    ContainerMul(iterator begin, iterator end, advcpp::Mutex & a_mutex, double & a_result) NOEXCEPTION;

    virtual void Run() NOEXCEPTION;

private:
    iterator m_begin;
    iterator m_end;
    Mutex & m_mutex;
    double & m_result;
};

} // namespace advcpp

#include "inl/thread_utils.inl"
#endif // THREAD_UTILS_H