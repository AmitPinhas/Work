#ifndef I_EVENT_STORAGE_POP
#define I_EVENT_STORAGE_POP

#include "i_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;
namespace smarthome
{

class IEventStoragePop
{
public:
    typedef SharedPointer<IEvent> IEventPtr;

    virtual ~IEventStoragePop() noexcept = default;

    virtual void Pop(IEventPtr& a_event) = 0;

    virtual size_t Size() const = 0;

protected:
    IEventStoragePop() = default;
    IEventStoragePop(const IEventStoragePop& a_rhs) = default;
    IEventStoragePop& operator =(const IEventStoragePop& a_rhs) = default;

};

} // namespace smarthome

#endif // I_EVENT_STORAGE_POP