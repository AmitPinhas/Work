#include "agent_creator.hpp"

namespace smarthome
{

AgentCreator::AgentCreator(IDeviceLoader & a_deviceLoader, ICreatorsContainer & a_creatorsContainer)
: m_deviceLoader(a_deviceLoader)
, m_creatorsContainer(a_creatorsContainer)
{
}

SharedPointer<IAgent> AgentCreator::GetAgent(SharedPointer<IDeviceInfo> a_deviceInfo) const
{
    auto  creator = m_creatorsContainer.Find(a_deviceInfo->GetType());
    if(!creator)
    {
        m_deviceLoader.Upload(a_deviceInfo->GetType());
        creator = m_creatorsContainer.Find(a_deviceInfo->GetType());
        if(!creator)
        {
            SharedPointer<IAgent> agent(0); //fix with deme agent;
            return agent;
            // log?
        }
    }
    return creator->Create(a_deviceInfo);
}

} // namespace smarthome
