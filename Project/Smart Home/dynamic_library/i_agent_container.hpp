#ifndef I_AGENT_CONTAINER_H
#define I_AGENT_CONTAINER_H

#include <vector>
#include "shared_pointer.hpp"
#include "i_agent.hpp"

namespace smarthome
{
class IAgentContainer
{
public:
    virtual ~IAgentContainer() = default;
    virtual std::vector<SharedPointer<IAgent> >& GetStorage() = 0;

protected:
    IAgentContainer() = default;
    IAgentContainer(IAgentContainer const& a_copy) = default;
    IAgentContainer & operator = (const IAgentContainer & a_agentContainer) = default;

};




}


#endif //i_agent_container.hpp
