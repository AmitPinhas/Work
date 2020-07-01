#ifndef WAITABLE_QUEUE_H
#define WAITABLE_QUEUE_H

#include <queue>
#include "Common.hpp"
#include "cond_var.hpp"
#include "i_pred_queue.hpp"

namespace advcpp
{

template <typename T>
class WaitableQueue : private UnCopyable
{
public:
    WaitableQueue(size_t a_capacity) THROW2(MutexException, CondVarException);
    // ~WaitableQueue() NOEXCEPTION = default;

    void Enqueue(const T & a_item) THROW2(MutexException, CondVarException);
    void Dequeue(T & a_item) THROW2(MutexException, CondVarException);

    size_t Size() const;
    bool Empty() const;

private:
    bool isFull() const;
    bool isEmpty() const; 

private:
    std::queue<T> m_queue;
    mutable Mutex m_mutex;
    CondVar m_condVar;
    size_t m_capacity;

};

template <typename T>
class IsFull : public IQueuePred
{
public:
    IsFull(const std::queue<T> & a_queue, size_t a_capacity);
    virtual ~IsFull();
    virtual bool operator()() const;

private:
    const std::queue<T> & m_queue;
    size_t m_capacity;
};

template <typename T>
class IsEmpty : public IQueuePred
{
public:
    IsEmpty(const std::queue<T> & a_queue);
    virtual ~IsEmpty();
    virtual bool operator()() const;

private:
    const std::queue<T> & m_queue;
};



} // namespace advcpp

#include "inl/waitable_queue.inl"
#endif // WAITABLE_QUEUE_H