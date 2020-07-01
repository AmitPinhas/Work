#ifndef I_CONTROLLER
#define I_CONTROLLER
#include "i_task.hpp"

#include "i_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class IController
{
public:
    virtual ~IController() noexcept = 0;
    virtual void Run(SharedPointer<IEvent> a_ievent) = 0;

protected:
    IController() = default;
    IController(const IController & a_controller)= default;
    IController & operator = (const IController & a_controller)= default;

};

inline IController::~IController() noexcept
{
}

} // namespace smart_home

#endif //  I_CONTROLLER