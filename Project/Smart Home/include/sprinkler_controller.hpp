#ifndef SPRINKLER_CONTROLLER_H
#define SPRINKLER_CONTROLLER_H

#include "i_agent.hpp"
#include "i_subscriber.hpp"
#include "event_structs.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class SprinklerController : public IAgent, public ISubscriber
{
public:
    explicit SprinklerController(Location a_location);

    ~SprinklerController() noexcept = default;
    SprinklerController(const SprinklerController& a_rhs) = default;
    SprinklerController& operator = (const SprinklerController& a_rhs) = default;

    void SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis);

    virtual void Notify(SharedPointer<IEvent> a_event);

    virtual  void Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI);

private:
    Topic createTopic();

private:
    Location m_location;
    SharedPointer<ISubscriber> m_SharedPtrThis;

};

} // namespace smarthome

#endif // SPRINKLER_CONTROLLER_H