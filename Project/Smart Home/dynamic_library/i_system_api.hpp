#ifndef I_SYSTEM_CONNECT_API_H
#define I_SYSTEM_CONNECT_API_H

#include "shared_pointer.hpp"
#include "i_event_receiver.hpp"
#include "i_subscriber.hpp"

namespace smarthome
{

class ISystemConnectApi
{
public:
    virtual ~ISystemConnectApi() noexcept = default;

    virtual SharedPointer<IEventReceiver> GetReciver() = 0;

    virtual void Subscribe(const Topic & a_topic, SharedPointer<ISubscriber> a_subscriber) = 0 ;

protected:
    ISystemConnectApi() = default;
    ISystemConnectApi(const ISystemConnectApi & a_copy) = default;
    ISystemConnectApi & operator = (const ISystemConnectApi & a_copy) = default;
    
};

} // namespace smarthome

#endif // I_SUBSCRIBE_FORM_H
