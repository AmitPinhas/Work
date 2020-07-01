#ifndef I_TIMER_H
#define I_TIMER_H

#include <ctime> // time_t

namespace smarthome
{

class ITimer
{
public:
    virtual ~ITimer() = default;    

    virtual time_t GetLeftTime(time_t a_time) const = 0;

    virtual time_t CalcNext(time_t a_period) const = 0;

protected:
    ITimer() = default;
    ITimer(const ITimer& a_rhs) = default;
    ITimer& operator = (const ITimer& a_rhs) = default;
};

} // namespace smarthome


#endif // I_TIMER_H