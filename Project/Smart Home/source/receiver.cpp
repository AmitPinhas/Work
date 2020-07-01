#include "receiver.hpp"

namespace smarthome
{

Receiver::Receiver(IEventStoragePush& a_eventStorageInsert)
: m_eventStorageInsert(a_eventStorageInsert)
{
}

void Receiver::Receive(IEventPtr a_event) const
{
   m_eventStorageInsert.Push(a_event); 
}

} // namespace smarthome