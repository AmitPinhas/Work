#ifndef I_CONNECT_ALL
#define I_CONNECT_ALL

#include <vector>
#include "i_agent.hpp"
#include "shared_pointer.hpp"
#include "agent_container.hpp"

namespace smarthome
{
class IConnector
{
public:
		virtual ~IConnector() = default;
		virtual void Connect(AgentContainer & a_agents) = 0;
    //virtual void ConnectEveryone(std::vector<SharedPointer<IAgent> >& a_agents) = 0;

protected:
    IConnector() = default;
    IConnector(IConnector const& a_copy) = default;
    IConnector & operator = (const IConnector & a_copy) = default;

};

}

#endif // i_connect_all.hpp
