#ifndef EVENTS_QUEUE_HPP
#define EVENTS_QUEUE_HPP

#include "i_event_storage_push.hpp"
#include "i_event_storage_pop.hpp"
#include "waitable_queue.hpp"
#include "i_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class EventsQueue : public IEventStoragePush , public IEventStoragePop
{
public:
    typedef SharedPointer<IEvent> IEventPtr;

    EventsQueue(size_t a_capacity);

    ~EventsQueue() = default;
    EventsQueue(const EventsQueue& a_rhs) = delete;
    EventsQueue& operator =(const EventsQueue& a_rhs) = delete;


    virtual void Push(IEventPtr a_event);
    virtual void Pop(IEventPtr& a_event);  
    virtual size_t Size() const;  

private:
    WaitableQueue<IEventPtr> m_events;

};

} // namespace smarthome

#include "inl/events_queue.inl"

#endif // EVENTS_QUEUE_HPP