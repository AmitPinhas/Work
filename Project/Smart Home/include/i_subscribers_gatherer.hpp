#ifndef I_SUBSCRIBERS_GATHERER_H
#define I_SUBSCRIBERS_GATHERER_H

#include "event_structs.hpp" // Topic
#include "shared_pointer.hpp"
#include "i_subscriber.hpp"

namespace smarthome
{

typedef SharedPointer<ISubscriber> SPISubscriber;

class ISubscribersGatherer
{
public:
    virtual ~ISubscribersGatherer() = default;

    virtual void Insert(const Topic& a_topic, SPISubscriber a_iSubscriber) = 0;

protected:
    ISubscribersGatherer() = default;
    ISubscribersGatherer(const ISubscribersGatherer& a_rhs) = default;
    ISubscribersGatherer& operator = (const ISubscribersGatherer& a_rhs) = default;

};

} // namespace smarthome


#endif // I_SUBSCRIBERS_GATHERER_H