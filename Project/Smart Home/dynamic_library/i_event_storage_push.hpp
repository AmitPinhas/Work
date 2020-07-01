#ifndef I_EVENT_STORAGE_PUSH
#define I_EVENT_STORAGE_PUSH

#include "i_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;
namespace smarthome
{

class IEventStoragePush
{
public:
    typedef SharedPointer<IEvent> IEventPtr;

    virtual ~IEventStoragePush() noexcept = default;

    virtual void Push(IEventPtr a_event) = 0;

    virtual size_t Size() const = 0;

protected:
    IEventStoragePush() = default;
    IEventStoragePush(const IEventStoragePush& a_rhs) = default;
    IEventStoragePush& operator =(const IEventStoragePush& a_rhs) = default;

};

} // namespace smarthome

#endif // I_EVENT_STORAGE_PUSH