#ifndef FACTORY_BOOTER_H
#define FACTORY_BOOTER_H

#include "i_factory_booter.hpp"
#include "i_agent_creator.hpp"

namespace smarthome
{

class FactoryBooter : public IFactoryBooter
{
public:
    explicit FactoryBooter(SharedPointer<IAgentCreator> a_agentCreator);

    ~FactoryBooter() = default;

    FactoryBooter(const FactoryBooter& a_rhs) = delete;

    FactoryBooter& operator =(const FactoryBooter& a_rhs) = delete;

    virtual void FillAgentContainer(std::vector<SharedPointer<IAgent> >& a_agents,
                                    const std::vector<SharedPointer<IDeviceInfo> >& a_deviceInfo) const;

private:
    static const size_t AGENT_NOT_FOUND = 0;

private:
    SharedPointer<IAgentCreator> m_agentCreator;

};

} // namespace smarthome

#endif // FACTORY_BOOTER_H