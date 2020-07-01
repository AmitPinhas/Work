#ifndef SEND_EVENTS_H
#define SEND_EVENTS_H

#include "thread.hpp"
#include "i_event.hpp"
#include "shared_pointer.hpp"
#include "i_event_receiver.hpp"

namespace smarthome
{

class SendEvents : public IRunnable
{
public:
    SendEvents(SharedPointer<IEvent> a_event, 
               size_t a_numEvents, 
               SharedPointer<IEventReceiver> a_ptrReceiver);

    ~SendEvents() noexcept = default;
    SendEvents(const SendEvents& a_rhs) = default;
    SendEvents& operator =(const SendEvents& a_rhs) = default;         

    virtual void Run() NOEXCEPTION;

private:
   SharedPointer<IEvent> m_event;     
   size_t m_numEvents;
   SharedPointer<IEventReceiver> m_ptrReceiver;

};

} // namespace smarthome

#endif // SEND_EVENTS_H