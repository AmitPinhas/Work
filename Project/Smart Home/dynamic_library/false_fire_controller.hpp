#ifndef FALSE_FIRE_CONTROLLER_H
#define FALSE_FIRE_CONTROLLER_H

#include "i_agent.hpp"
#include "i_subscriber.hpp"
#include "event_structs.hpp"
#include "shared_pointer.hpp"
#include "atomic_value.hpp"

using namespace advcpp;

namespace smarthome
{

class FalseFireControlller : public IAgent, public ISubscriber
{
public:
    explicit FalseFireControlller(Location a_location);

    ~FalseFireControlller() noexcept = default;
    FalseFireControlller(const FalseFireControlller& a_rhs) = default;
    FalseFireControlller& operator = (const FalseFireControlller& a_rhs) = default;

    int GetValue() const;

    void SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis);

    virtual void Notify(SharedPointer<IEvent> a_event);

    virtual  void Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI);


private:
    Topic createTopic();

private:
    Location m_location;
    SharedPointer<ISubscriber> m_SharedPtrThis;
    AtomicValue<int> m_numEvents;

};

// inline bool operator==(FalseFireControlller* a_lhs, FalseFireControlller* a_rhs)
// {
//     return a_lhs==a_rhs;
// }



} // namespace smarthome

#endif // SPRINKLER_CONTROLLER_H