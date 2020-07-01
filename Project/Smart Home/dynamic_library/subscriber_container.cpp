#include "subscriber_container.hpp"


void SubscriberContainer::Subscribe(const Topic & a_topic, SharedPointer<ISubscriber> a_subscriber)
{
    m_subscribers[a_topic] = a_subscriber;
}