
namespace advcpp
{

template <typename T>
WaitableQueue<T>::WaitableQueue(size_t a_capacity) THROW2(MutexException, CondVarException)
: m_capacity(a_capacity)
{
}

template <typename T>
size_t WaitableQueue<T>::Size() const THROW1(MutexException)
{
    m_mutex.Lock();

    size_t size = m_queue.size();

    m_mutex.UnLock();

    return size;
}

template <typename T>
bool WaitableQueue<T>::Full() const THROW1(MutexException)
{
    return Size() == m_capacity;
}

template <typename T>
bool WaitableQueue<T>::Empty() const THROW1(MutexException)
{
    return Size() == 0;   
}

template <typename T>
bool WaitableQueue<T>::isFull() const NOEXCEPT
{
    return m_queue.size() == m_capacity;
}

template <typename T>
bool WaitableQueue<T>::isEmpty() const NOEXCEPT
{
    return m_queue.size() == 0; 
}

template <typename T>
void WaitableQueue<T>::Enqueue(const T& a_value) THROW2(MutexException, CondVarException)
{
	{
		Guard locker(m_mutex);
		m_cv.Wait(m_mutex, IsFullPred<T>(*this));
    	m_queue.push(a_value);
	}
    m_cv.Notify();  
}

template <typename T>
void WaitableQueue<T>::Dequeue(T& a_value) THROW2(MutexException, CondVarException)
{
	{
		Guard locker(m_mutex);
		m_cv.Wait(m_mutex, IsEmptyPred<T>(*this));
        a_value = m_queue.front();
        m_queue.pop();
	}
    m_cv.Notify();   
}

template <typename T>
IsFullPred<T>::IsFullPred(WaitableQueue<T>& a_queue)
: m_queue(a_queue)
{
}

template <typename T>
bool IsFullPred<T>::operator()() const THROW1(MutexException)
{
	return m_queue.isFull();
}

template <typename T>
IsEmptyPred<T>::IsEmptyPred(WaitableQueue<T>& a_queue)
: m_queue(a_queue)
{
}

template <typename T>
bool IsEmptyPred<T>::operator()() const THROW1(MutexException)
{
	return m_queue.isEmpty();
}

} // namespace advcpp
