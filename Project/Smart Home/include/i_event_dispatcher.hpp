#ifndef I_EVENT_DISPATCHER_H
#define I_EVENT_DISPATCHER_H

namespace smarthome
{

class IEventDispatcher
{
public:
    virtual ~IEventDispatcher() noexcept = default;

    virtual void Pause() = 0;

    virtual void Resume() = 0;

    virtual void ShutDown() = 0;

protected:
    IEventDispatcher() = default;
    IEventDispatcher(const IEventDispatcher& a_rhs) = default;
    IEventDispatcher& operator =(const IEventDispatcher& a_rhs) = default;    

};

} // namespace smarthome

#endif // I_EVENT_DISPATCHER_H