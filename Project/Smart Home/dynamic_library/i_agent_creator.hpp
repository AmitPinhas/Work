#ifndef I_AGENT_CREATOR_H
#define I_AGENT_CREATOR_H

#include "shared_pointer.hpp"
#include "i_agent.hpp"
#include "i_device_info.hpp"

namespace smarthome
{

class IAgentCreator
{
public:
    virtual ~IAgentCreator() = default;

    virtual SharedPointer<IAgent> GetAgent(SharedPointer<IDeviceInfo> a_deviceInfo) const = 0;
    
protected:
    IAgentCreator() = default;
    IAgentCreator(const IAgentCreator& a_rhs) = default;
    IAgentCreator& operator =(const IAgentCreator& a_rhs) = default;

};

} // namespace smarthome

#endif // I_AGENT_CREATOR_H