#ifndef EVENTS_QUEUE_INL
#define EVENTS_QUEUE_INL

namespace smarthome
{

inline void EventsQueue::Push(IEventPtr a_event)
{
    m_events.Enqueue(a_event);
}

inline void EventsQueue::Pop(IEventPtr& a_event)
{
    m_events.Dequeue(a_event);
}

inline size_t EventsQueue::Size() const
{
    return m_events.Size();
} 

} // namespace smarthome

#endif // EVENTS_QUEUE_INL