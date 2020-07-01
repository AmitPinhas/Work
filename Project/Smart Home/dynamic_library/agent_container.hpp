#ifndef AGENT_CONTAINER_H
#define AGENT_CONTAINER_H

// #include <vector>
// #include "shared_pointer.hpp"
// #include "i_agent.hpp"
#include "i_agent_container.hpp"

namespace smarthome
{


class AgentContainer: public IAgentContainer
{
public:
    AgentContainer() = default;
    ~AgentContainer() = default;
    std::vector<SharedPointer<IAgent> >& GetStorage();

protected:
    AgentContainer(AgentContainer const& a_copy) = default;
    AgentContainer & operator = (const AgentContainer & a_agentContainer) = default;

private:
    std::vector<SharedPointer<IAgent> > m_storage;
};

}


#endif // agent_container.hpp