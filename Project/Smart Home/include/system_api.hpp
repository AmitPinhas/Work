#ifndef SUBSCRIBE_FORM_H
#define SUBSCRIBE_FORM_H

#include "i_system_api.hpp"
#include "i_subscribers_updator.hpp"

namespace smarthome
{

class SystemConnectApi : public ISystemConnectApi
{
public:
    SystemConnectApi(SharedPointer<IEventReceiver> a_reciver,
                                SharedPointer<ISubscriberUpdator> a_updator);
    virtual SharedPointer<IEventReceiver> GetReciver();
    virtual void Subscribe(const Topic & a_topic, SharedPointer<ISubscriber> a_subscriber);

private:
    SharedPointer<IEventReceiver> m_reciver;
    SharedPointer<ISubscriberUpdator> m_updator;
};

} // namespace smarthome

#endif // SUBSCRIBE_FORM_H
