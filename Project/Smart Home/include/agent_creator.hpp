#ifndef AGENT_CREATOR_H
#define AGENT_CREATOR_H

#include "i_agent_creator.hpp"
#include "i_device_loader.hpp"
#include "i_creators_container.hpp"
#include "i_agent.hpp"

namespace smarthome
{

class AgentCreator : public IAgentCreator
{
public:
    AgentCreator(IDeviceLoader & a_deviceLoader, ICreatorsContainer & a_creatorsContainer);
    ~AgentCreator() = default;
    AgentCreator(const AgentCreator & a_rhs) = delete;
    AgentCreator & operator = (const AgentCreator & a_rhs) = delete;

    virtual SharedPointer<IAgent> GetAgent(SharedPointer<IDeviceInfo> a_deviceInfo) const;

private:
    IDeviceLoader & m_deviceLoader; 
    ICreatorsContainer & m_creatorsContainer;
};

} // namespace smarthome


#endif // AGENT_CREATOR_H