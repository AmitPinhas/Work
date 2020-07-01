#include "connector.hpp"
#include <unistd.h>
#include <algorithm>


namespace smarthome
{

Connector::Connector(/*SharedPointer<IEventReceiver> a_reciver, SharedPointer<ISubscriberUpdator> a_updator*/ SharedPointer<ISystemConnectApi> a_sysApi)
               // new SystemConnectApi
:	m_systemAPI( a_sysApi )
{
}

void Connector::Connect(AgentContainer & a_agents)
{
	for_each(a_agents.GetStorage().begin(), a_agents.GetStorage().end(), [api=this->m_systemAPI](auto agent){ agent->Connect(api) ;} );	
   //for(size_t i = 0; i < a_agents.GetStorage().size(); ++i)
   //{
     //  (a_agents.GetStorage())[i]->Connect(m_formToDevice);
   //}
}

}
