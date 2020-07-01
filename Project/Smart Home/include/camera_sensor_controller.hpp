#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "i_agent.hpp"
#include "shared_pointer.hpp"
#include "i_system_api.hpp"
#include "event_structs.hpp"
#include "i_event_receiver.hpp"

namespace smarthome
{
class CameraSenCntrl: public IAgent, public ISubscriber
{
public:
    CameraSenCntrl(Location a_location, size_t a_numEvents);

    ~CameraSenCntrl() noexcept = default;
    CameraSenCntrl(const CameraSenCntrl& a_rhs) = default;
    CameraSenCntrl& operator =(const CameraSenCntrl& a_rhs) = default;

    void SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis);

    virtual void Notify(SharedPointer<IEvent> a_event);

    virtual  void Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI);

private:
    SharedPointer<IEvent> createEvent();

    Topic createTopic();


private:
    Location m_location;        
    size_t m_numEvents;
    SharedPointer<IEventReceiver> m_ptrReceiver;
    SharedPointer<ISubscriber> m_SharedPtrThis;
};
}


#endif //camera.hpp