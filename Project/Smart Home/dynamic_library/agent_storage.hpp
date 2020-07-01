#ifndef AGENT_STORAGE_HPP
#define AGENT_STORAGE_HPP

#include "sensor.hpp"
#include "controller.hpp"
#include "agent_struct.hpp"
#include "i_controller.hpp"
#include "shared_pointer.hpp"

namespace smarthome
{

class AgentStorage: public IAgentStorage
{
public:
	void Add(Agent const& a_agent, SharedPointer<IController> a_cntr);

private:
	std::vector<Agent> m_agents;
	std::vector<
};

}



#endif /*agent_storage.hpp*/
