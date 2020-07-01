#ifndef ISUBSCRIBERS_HPP
#define ISUBSCRIBERS_HPP

#include <vector>
#include "i_subscriber.hpp"
#include "shared_pointer.hpp" // SharedPointer
#include "i_event.hpp"


using namespace advcpp;

namespace smarthome
{

class ISubscriberUpdator
{
public: 
    virtual ~ISubscriberUpdator() = default;
    virtual void Subscribe(const Topic a_topic, SharedPointer<ISubscriber>  a_iSubscriber) = 0;
    virtual void UnSubscribe(const std::vector<Topic> & a_topics, SharedPointer<ISubscriber> a_iSubscriber) = 0;

protected:
    ISubscriberUpdator() = default;
    ISubscriberUpdator(ISubscriberUpdator const& a_sub) = default;
    ISubscriberUpdator & operator = (const ISubscriberUpdator & a_sub) = default;


};


}


#endif
