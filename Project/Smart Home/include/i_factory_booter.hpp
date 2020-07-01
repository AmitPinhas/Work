#ifndef I_FACTORY_BOOTER_H
#define I_FACTORY_BOOTER_H

#include <vector>
#include <string>
#include "i_agent.hpp"
#include "shared_pointer.hpp"
#include "i_device_info.hpp"

namespace smarthome
{

class IFactoryBooter
{
public:
    ~IFactoryBooter() = default;

    virtual void FillAgentContainer(std::vector<SharedPointer<IAgent> >& a_agents,
                                    const std::vector<SharedPointer<IDeviceInfo> >& a_deviceInfo) const = 0;

protected:
    IFactoryBooter() = default;
    IFactoryBooter(const IFactoryBooter& a_rhs) = default;
    IFactoryBooter& operator =(const IFactoryBooter& a_rhs) = default;

};

} // namespacehome

#endif // I_FACTORY_BOOTER_H