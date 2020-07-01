#ifndef WAITABLE_QUEUE_H
#define WAITABLE_QUEUE_H

#include <queue>
#include "common.hpp"
#include "mutex.hpp"
#include "conditional_variable.hpp"

namespace advcpp
{

template <typename T>
class WaitableQueue : private UnCopyable
{
public:
    explicit WaitableQueue(size_t a_capacity) THROW2(MutexException, CondVarException);

    // ~WaitableQueue() NOEXCEPT; = default

    void Enqueue(const T& a_value) THROW2(MutexException, CondVarException);

    void Dequeue(T& a_value) THROW2(MutexException, CondVarException);

    size_t Size() const THROW1(MutexException);
    bool Full() const THROW1(MutexException);
    bool Empty() const THROW1(MutexException);
    
    template <typename A>
	friend class IsFullPred;
	
    template <typename B>
	friend class IsEmptyPred;
		
private:
    bool isFull() const NOEXCEPT;
    bool isEmpty() const NOEXCEPT;

private:    
    const size_t m_capacity;
    mutable Mutex m_mutex;
    std::queue<T> m_queue;
    ConditionalVariable m_cv;

};

template <typename T>
class IsFullPred 
{
public:
	explicit IsFullPred(WaitableQueue<T>& a_queue);
	
	bool operator()() const THROW1(MutexException);

private:
	WaitableQueue<T>& m_queue;
};

template <typename T>
class IsEmptyPred 
{
public:
	explicit IsEmptyPred(WaitableQueue<T>& a_queue);
	
	bool operator()() const THROW1(MutexException);

private:
	WaitableQueue<T>& m_queue;
};

} // namespace advcpp

#include "waitable_queue.inl"

#endif // WAITABLE_QUEUE_H
