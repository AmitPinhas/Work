#include "broadcast.hpp"

#include "event_executer.hpp"

#include <iostream>

namespace smarthome
{

Broadcast::Broadcast(SubscribersStorage & a_subscribers)
: m_subscribers(a_subscribers)
, m_threadpool(MAX_TASKS)
{
}

void Broadcast::Dispatch(SharedPointer<IEvent> a_event)
{    
    std::cout << "the topic that weve got: " << a_event->GetTopic();
    auto sublist = m_subscribers.Find(a_event->GetTopic());

    if(0 == sublist->Size())
    {
        std::cout << "to logger no controllers were found to topic: " << a_event->GetTopic().m_type.m_type;
        return;
    }

    SharedPointer<ITask> containerTask(new EventExecuter(a_event, sublist));
    m_threadpool.DispatchTask(containerTask);
}

void Broadcast::ShutDown()
{
    m_threadpool.ShutDown();
}

} // namespace smarthome
