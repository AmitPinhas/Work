#ifndef SAFE_QUEUE_HPP
#define SAFE_QUEUE_HPP
#include <queue>

#include "common.hpp"
#include "mutex.hpp"

namespace advcpp
{

template<typename T>
class IsQEmpty;

template<typename T>
class IsQFull;

template<typename T>
class SafeQueue : private UnCopyAble
{
public:
    template<typename U>
    friend class IsQFull;

    template<typename U>
    friend class IsQEmpty;

public:
    explicit SafeQueue(size_t a_size) THROW2(MutexExeption, CondVarExeption);
    //~SafeQueue(); deafult

    void EnQueue(T const& a_value) THROW2(MutexExeption, CondVarExeption);
    void DeQueue(T& a_retVal) THROW2(MutexExeption, CondVarExeption);

    size_t Size();
    size_t Capacity();

private:
    bool IsEmpty() const;
    bool IsFull() const;

private:
    std::queue<T> m_queue;
    Mutex m_mutex;
    CondVar m_condVar;
    const size_t m_capacity;
};



template<typename T>
class IsQFull
{
public:
    IsQFull(SafeQueue<T> const& a_queue);
    ~IsQFull();

    bool operator()() const;

private:
    SafeQueue<T> const& m_queue;
};

template<typename T>
class IsQEmpty
{
public:
    IsQEmpty(SafeQueue<T> const& a_queue);
    ~IsQEmpty();

    bool operator()() const;

private:
    SafeQueue<T> const& m_queue;
};


}//advcpp
#include "inl/safe_queue.inl"
#endif//SAFE_QUEUE_HPP