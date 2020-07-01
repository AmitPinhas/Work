
namespace advcpp
{

template<typename T>
SafeQueue<T>::SafeQueue(size_t a_capacity) THROW2(MutexExeption, CondVarExeption)
: m_queue()
, m_mutex()
, m_condVar()
, m_capacity(a_capacity)
{
}

template<typename T>
void SafeQueue<T>::EnQueue(T const& a_value) THROW2(MutexExeption, CondVarExeption)
{
    {
        Guard locker(m_mutex);

        IsQFull<T> pred(*this);
        m_condVar.Wait(m_mutex, pred);
        m_queue.push(a_value);
    }
    m_condVar.Nutify();
}

template<typename T>
void SafeQueue<T>::DeQueue(T & a_retVal) THROW2(MutexExeption, CondVarExeption)
{
    {
        Guard Locker(m_mutex);
        
        IsQEmpty<T> pred(*this);
        m_condVar.Wait(m_mutex, pred);
        a_retVal = m_queue.front();
        m_queue.pop();
    }
    m_condVar.Nutify();
}

template<typename T>
size_t SafeQueue<T>::Size()
{
    m_mutex.Lock();
    size_t size = m_queue.size();
    m_mutex.UnLock();

    return size; 
}

template<typename T>
size_t SafeQueue<T>::Capacity()
{
    return m_capacity; 
}

template<typename T>
bool SafeQueue<T>::IsEmpty() const
{
    return m_queue.size() == 0;
}

template<typename T>
bool SafeQueue<T>::IsFull() const
{
    return m_queue.size() == m_capacity;
}

template<typename T>
IsQFull<T>::IsQFull(SafeQueue<T> const& a_queue)
: m_queue(a_queue)
{
}

template<typename T>
IsQFull<T>::~IsQFull()
{
}

template<typename T>
bool IsQFull<T>::operator()() const
{
    return m_queue.IsFull();
}

template<typename T>
IsQEmpty<T>::IsQEmpty(SafeQueue<T> const& a_queue)
: m_queue(a_queue)
{
}

template<typename T>
IsQEmpty<T>::~IsQEmpty()
{
}

template<typename T>
bool IsQEmpty<T>::operator()() const
{
    return m_queue.IsEmpty();
}

}//namespace advcpp



