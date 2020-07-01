#ifndef I_AGENT_H
#define I_AGENT_H

#include "shared_pointer.hpp"
#include "i_system_api.hpp"

namespace smarthome
{

class IAgent
{
public:
    virtual ~IAgent() noexcept = 0;

    virtual void Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI) = 0;

protected:
    IAgent() = default;
    IAgent(const IAgent & a_sensor) = default;
    IAgent & operator = (const IAgent & a_sensor) = default;

};

} // namespace smarthome

#endif // I_AGENT_H
