#ifndef RECEIVER_H
#define RECEIVER_H

#include "i_event_receiver.hpp" 
#include "i_event.hpp"
#include "i_event_storage_push.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class Receiver : public IEventReceiver
{
public:
    typedef SharedPointer<IEvent> IEventPtr;    

    Receiver(IEventStoragePush& a_eventStorageInsert);

    ~Receiver() = default;
    Receiver(const Receiver& a_rhs) = delete;
    Receiver& operator =(const Receiver& a_rhs) = delete;

    virtual void Receive(IEventPtr a_event) const;

private:
    IEventStoragePush& m_eventStorageInsert; 

};

} // namespace smarthome

#endif // RECEIVER_H