#ifndef EVENT_2_LIST_RUNNER_H
#define EVENT_2_LIST_RUNNER_H

#include "i_event.hpp"
#include "i_controller.hpp"
#include "i_task.hpp"
#include "shared_pointer.hpp"
#include "i_subscribers_list.hpp"
using namespace advcpp;

namespace smarthome
{

class Event2ListRunner : public ITask
{
public:
    Event2ListRunner(SharedPointer<IEvent> a_event, SharedPointer<ISubscribersList>  a_cContainer);
    ~Event2ListRunner() = default;
    Event2ListRunner(const Event2ListRunner & a_event2ListRunner) = delete;
    Event2ListRunner & operator = (const Event2ListRunner & a_event2ListRunner) = delete;

    virtual void Run();

private:
    SharedPointer<IEvent> m_ievent;
    SharedPointer<ISubscribersList> m_sContainer;
};


} // namespace smarthome


#endif // EVENT_2_LIST_RUNNER_H