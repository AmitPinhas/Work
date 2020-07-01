#ifndef EVENT_EXEXCUTER_H
#define EVENT_EXEXCUTER_H

#include "i_event.hpp"
#include "i_controller.hpp"
#include "i_task.hpp"
#include "shared_pointer.hpp"
#include "i_subscribers_list.hpp"
using namespace advcpp;

namespace smarthome
{

class EventExecuter : public ITask
{
public:
    EventExecuter(SharedPointer<IEvent> a_event, SharedPointer<ISubscribersList>  a_cContainer);
    ~EventExecuter() = default;
    EventExecuter(const EventExecuter & a_EventExecuter) = delete;
    EventExecuter & operator = (const EventExecuter & a_EventExecuter) = delete;

    virtual void Run();

private:
    SharedPointer<IEvent> m_ievent;
    SharedPointer<ISubscribersList> m_sContainer;
};


} // namespace smarthome


#endif // EVENT_EXEXCUTER_H