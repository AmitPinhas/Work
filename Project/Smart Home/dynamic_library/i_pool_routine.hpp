#ifndef I_POOL_ROUTINE_H
#define I_POOL_ROUTINE_H

#include "thread.hpp"
#include "i_pool_routine.hpp"
#include "waitable_queue.hpp"
#include "i_task.hpp"
#include "shared_pointer.hpp"
#include "atomic_value.hpp"

namespace advcpp
{

class IPoolRoutine : public IRunnable
{
public:
    virtual ~IPoolRoutine() NOEXCEPTION = 0;
    virtual void Run() NOEXCEPTION = 0;
    virtual void ShutDown() = 0;
    virtual size_t GetStatus() const = 0;

};

inline IPoolRoutine::~IPoolRoutine() NOEXCEPTION
{
}

} // namespace advcpp

#endif // I_POOL_ROUTINE_H