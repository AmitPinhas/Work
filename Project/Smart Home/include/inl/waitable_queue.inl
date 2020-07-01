#include "waitable_queue.hpp"

namespace advcpp
{

template <typename T>
WaitableQueue<T>::WaitableQueue(size_t a_capacity) THROW2(MutexException, CondVarException)
: m_capacity(a_capacity)
{    
}

template <typename T>
void WaitableQueue<T>::Enqueue(const T & a_item) THROW2(MutexException, CondVarException)
{  
    {
        Guard guard(m_mutex);

        IsFull<T> isFull(m_queue, m_capacity);
        m_condVar.Wait(m_mutex, isFull);
        m_queue.push(a_item);
    }

    m_condVar.Notify();
}

template <typename T>
void WaitableQueue<T>::Dequeue(T & a_item) THROW2(MutexException, CondVarException)
{
    {
        Guard guard(m_mutex);

        IsEmpty<T> isEmpty(m_queue);
        
        m_condVar.Wait(m_mutex, isEmpty);
        
        a_item = m_queue.front();
        m_queue.pop();
    }

    m_condVar.Notify();
}

template <typename T>
size_t WaitableQueue<T>::Size() const
{
    m_mutex.Lock();
    size_t size = m_queue.size();
    m_mutex.UnLock();

    return size;
}

template <typename T>
bool WaitableQueue<T>::Empty() const
{
    return 0 == Size();
}

template <typename T>
bool WaitableQueue<T>::isFull() const
{
    return m_capacity == m_queue.size();
}

template <typename T>
bool WaitableQueue<T>::isEmpty() const
{
    return 0 == m_queue.size();
}

template <typename T>
IsFull<T>::IsFull(const std::queue<T> & a_queue, size_t a_capacity)
: m_queue(a_queue)
, m_capacity(a_capacity)
{
}

template <typename T>
IsFull<T>::~IsFull()
{
}


template <typename T>
inline bool IsFull<T>::operator()() const
{
    return m_capacity == m_queue.size();
}

template <typename T>
IsEmpty<T>::IsEmpty(const std::queue<T> & a_queue)
: m_queue(a_queue)
{
}

template <typename T>
IsEmpty<T>::~IsEmpty()
{
}

template <typename T>
inline bool IsEmpty<T>::operator()() const
{
    return 0 == m_queue.size();
}


} // namespace advcpp