#include "subscribers_list.hpp"
#include <algorithm>
namespace smarthome
{

void SubscribersList::Dispatch(SharedPointer<IEvent> a_ievent)
{
    for_each(m_subscribers.begin(), m_subscribers.end(), 
            [a_ievent](SharedPointer<ISubscriber> a_iSubscriber){a_iSubscriber->Notify(a_ievent);});
}

void SubscribersList::Add(SharedPointer<ISubscriber> a_iSubscriber)
{
    m_subscribers.push_back(a_iSubscriber);
}

void SubscribersList::Remove(SharedPointer<ISubscriber> a_iSubscriber)
{
    auto it = find(m_subscribers.begin(), m_subscribers.end(), a_iSubscriber);
    m_subscribers.erase(it);
}

size_t SubscribersList::Size() const
{
    return m_subscribers.size();
}

} // namespace smarthome
