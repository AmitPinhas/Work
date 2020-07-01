#include "agent_container.hpp"

namespace smarthome
{

std::vector<SharedPointer<IAgent> >& AgentContainer::GetStorage()
{
    return m_storage;
}

}
