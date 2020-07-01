#ifndef SPRINKLER_FLAME_CONTROLLER_H
#define SPRINKLER_FLAME_CONTROLLER_H

#include "i_agent.hpp"
#include "i_subscriber.hpp"
#include "event_structs.hpp"
#include "shared_pointer.hpp"
#include "atomic_value.hpp"

using namespace advcpp;

namespace smarthome
{

class SprinklerFlameController : public IAgent, public ISubscriber
{
public:
    explicit SprinklerFlameController(Location a_location, AtomicValue<int> & a_atomic);

    ~SprinklerFlameController() noexcept = default;
    SprinklerFlameController(const SprinklerFlameController& a_rhs) = default;
    SprinklerFlameController& operator = (const SprinklerFlameController& a_rhs) = default;

    void SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis);

    virtual void Notify(SharedPointer<IEvent> a_event);

    virtual  void Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI);

private:
    Topic createTopic();

private:
    Location m_location;
    SharedPointer<ISubscriber> m_SharedPtrThis;
    AtomicValue<int> & m_atomic;


};

} // namespace smarthome

#endif // SPRINKLER_FLAME_CONTROLLER_H