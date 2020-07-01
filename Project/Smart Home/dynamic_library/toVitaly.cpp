#ifndef I_SUBSCRIBER_H
#define I_SUBSCRIBER_H

#include "i_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;
namespace smarthome
{

struct SubId
{
    std::string m_id;
};

class ISubscriber
{
public:
    virtual ~ISubscriber() noexcept = 0;

    virtual void Notify(SharedPointer<IEvent> a_event) = 0;
    virtual SubId GetId() const = 0;

protected:
    ISubscriber() = default;
    ISubscriber(ISubscriber const& a_event) = default;
    ISubscriber & operator = (const ISubscriber & a_event) = default;

};

} // namespace smarthome

#endif // I_SUBSCRIBER_H