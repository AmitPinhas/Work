#ifndef I_GATHERED_SUBSCRIBERS_CONTAINER_H
#define I_GATHERED_SUBSCRIBERS_CONTAINER_H

#include <utility> // std::pair
#include <set> 
#include "event_structs.hpp"
#include "shared_pointer.hpp"
#include "i_subscriber.hpp"

namespace smarthome
{

typedef std::pair< std::set<Topic>, std::set<advcpp::SharedPointer<ISubscriber> > > Gathered;

class IGatheredSubscribersContainer
{
public:
    virtual ~IGatheredSubscribersContainer() = default;

    virtual Gathered PopGathered() = 0;

    virtual bool HasMore() const = 0;

protected:
    IGatheredSubscribersContainer() = default;
    IGatheredSubscribersContainer(const IGatheredSubscribersContainer& a_rhs) = default;
    IGatheredSubscribersContainer& operator = (const IGatheredSubscribersContainer& a_rhs) = default;

};

} // namespace smarthome

#endif // I_GATHERED_SUBSCRIBERS_CONTAINER_H