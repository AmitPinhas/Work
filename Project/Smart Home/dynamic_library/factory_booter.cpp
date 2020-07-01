#include "factory_booter.hpp"

namespace smarthome
{

FactoryBooter::FactoryBooter(SharedPointer<IAgentCreator> a_agentCreator)
: m_agentCreator(a_agentCreator)
{
}

void FactoryBooter::FillAgentContainer(std::vector<SharedPointer<IAgent> >& a_agents,
                                       const std::vector<SharedPointer<IDeviceInfo> >& a_deviceInfo) const
{
    for(const auto& deviceInfo: a_deviceInfo)
    {
        SharedPointer<IAgent> newAgent = m_agentCreator->GetAgent(deviceInfo);

        if(AGENT_NOT_FOUND == newAgent)
        {
            std::cout << "file " << __FILE__ << "function: " << __func__ << "line: " << __LINE__ << std::endl;
            std::cout << "device info: " << deviceInfo->GetType() << std::endl;
        }

        a_agents.push_back(newAgent);
    }
}                        

} // namespace smarthome