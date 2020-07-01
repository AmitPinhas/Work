#include "sprinklers.hpp"

#include <iostream>

namespace smarthome
{

void Sprinklers::Work(SharedPointer<IEvent> a_ievent)
{
    std::cout << "event type: "<< a_ievent->GetTopic().m_type.m_type << " sprinklers on \n";
}

} // namespace smarthome
