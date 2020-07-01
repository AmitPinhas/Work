#ifndef I_SUBSCRIBERS_LIST_NOTIFIER_H
#define I_SUBSCRIBERS_LIST_NOTIFIER_H


#include "i_event.hpp" // event
#include "shared_pointer.hpp"

using namespace advcpp;
namespace smarthome
{

class ISubscribersListNotifier 
{
public:
    virtual ~ISubscribersListNotifier() noexcept = default;
    virtual void Notifi(SharedPointer<IEvent> a_event) = 0;
    virtual void ShutDown() = 0;

protected:
    ISubscribersListNotifier() = default;
    ISubscribersListNotifier(const ISubscribersListNotifier & a_ISubscribersListNotifier) = default;
    ISubscribersListNotifier & operator = (const ISubscribersListNotifier & a_ibroadcast) = default;

};

} // namespace smarthome

#endif // I_SUBSCRIBERS_LIST_NOTIFIER_H