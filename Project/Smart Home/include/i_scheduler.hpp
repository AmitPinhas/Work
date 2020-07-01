#ifndef I_SCHEDULER_H
#define I_SCHEDULER_H

namespace smarthome
{

class IScheduler
{
public:
    virtual ~IScheduler() = default;

    virtual void Run() = 0;

    virtual void Shutdown() = 0;

protected:
    IScheduler() = default;
    IScheduler(const IScheduler& a_rhs) = default;
    IScheduler& operator = (const IScheduler& a_rhs) = default;

};

} // namespace smarthome

#endif // I_SCHEDULER_H