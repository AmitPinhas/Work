#ifndef I_SUBSCRIBERS_GROUP_H
#define I_SUBSCRIBERS_GROUP_H

#include "shared_pointer.hpp"
#include "i_event.hpp"

namespace smarthome
{
    
typedef advcpp::SharedPointer<IEvent> SPIEvnt;

class ISubscribersGroup
{
public:
    virtual ~ISubscribersGroup() = default;

    virtual void Notify(SPIEvnt a_iEvent) = 0;

    virtual void Shutdown() = 0;

protected:
    ISubscribersGroup() = default;
    ISubscribersGroup(const ISubscribersGroup& a_rhs) = default;
    ISubscribersGroup& operator = (const ISubscribersGroup& a_rhs) = default;

};

} // namespace smarthome


#endif // I_SUBSCRIBERS_GROUP_H