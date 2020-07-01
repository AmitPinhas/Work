#ifndef "I_AGENT_STORAGE.HPP"
#define "I_AGENT_STORAGE.HPP"

#include "Common.hpp"

namespace smarthome
{

typedef class Agent; // class agent can be a sensor or controller

class IAgentStorage: private UnCopyable
{
public:
	virtual void Add(Agent const& a_agent) = 0;
	virtual ~IAgentStorage() = default;

};


}


#endif /*i_agent_storage.hpp*/
