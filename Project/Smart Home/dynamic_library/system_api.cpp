#include "system_api.hpp"

namespace smarthome 
{

SystemConnectApi::SystemConnectApi(SharedPointer<IEventReceiver> a_reciver, SharedPointer<ISubscriberUpdator> a_updator)
:	m_reciver(a_reciver)
,	m_updator(a_updator)
{
}


SharedPointer<IEventReceiver> SystemConnectApi::GetReciver()
{
    return m_reciver;
}

void SystemConnectApi::Subscribe(const Topic & a_topic , SharedPointer<ISubscriber> a_subscribe)
{
   m_updator->Subscribe(a_topic, a_subscribe);
}

} // namespace smarthome 
