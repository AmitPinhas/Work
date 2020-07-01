#ifndef SUBSCRIBER_CONTAINER_H
#define SUBSCRIBER_CONTAINER_H

namespace smarthome
{
class SubscriberContainer: public  ISubscriberUpdator, public ISubscribersFinder
{
public:
    SubscriberContainer() = default;
    ~SubscriberContainer() = default;
    void Subscribe(const Topic & a_topic, SharedPointer<ISubscriber> a_subscriber);


protected:
    SubscriberContainer() = default;
    SubscriberContainer(SubscriberContainer const& a_finder) = default;
    SubscriberContainer & operator = (const SubscriberContainer & a_finder) = default;


private:
    std::map<Topic, ControllersContainer> m_subscribers;
    
    /* data */
};


}


#endif