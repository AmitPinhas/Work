#include "subscribers_list_notifier.hpp"


#include <iostream>
#include "event_2_list_runner.hpp"

namespace smarthome
{

SubscribersListNotifier::SubscribersListNotifier(ISubscribersFinder & a_finder, size_t NumOfTasks)
: m_finder(a_finder)
, m_threadpool(NumOfTasks)
{
}

void SubscribersListNotifier::Notifi(SharedPointer<IEvent> a_event)
{    
    auto sublist = m_finder.Find(a_event->GetTopic());

    if(0 == sublist->Size())
    {
        std::cout << "file: " << __FILE__ << "function: " << __func__ << "line: " << __LINE__ << '\n';
        return;
    }

    SharedPointer<ITask> notifiAllSubscribersInList(new Event2ListRunner(a_event, sublist));
    m_threadpool.DispatchTask(notifiAllSubscribersInList);
}

void SubscribersListNotifier::ShutDown()
{
    m_threadpool.ShutDown();
}

} // namespace smarthome
