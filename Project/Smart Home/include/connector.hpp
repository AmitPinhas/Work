#ifndef CONNECT_ALL
#define CONNECT_ALL

#include <vector>
#include "i_connector.hpp"
#include "i_agent.hpp"
#include "shared_pointer.hpp"
#include "system_api.hpp"
#include "i_system_api.hpp"
#include "agent_container.hpp"

namespace smarthome
{
class Connector: public IConnector
{
public:
    explicit Connector(/*SharedPointer<IEventReceiver> a_reciver,
                                SharedPointer<ISubscriberUpdator> a_updator*/ SharedPointer<ISystemConnectApi> a_sysApi); // must get in construct the System API
    ~Connector() = default;
	virtual void Connect(AgentContainer & a_agents);
	//void Connect(std::vector<SharedPointer<IAgent> >& a_agents);

protected:
    Connector(Connector const& a_copy) = default;
    Connector & operator = (const Connector & a_copy) = default;

private:
    SharedPointer<ISystemConnectApi> m_systemAPI;
    

};

}


#endif //connect_all.hpp
