#ifndef SPRINKLERS_H
#define SPRINKLERS_H

#include "i_device.hpp"

namespace smarthome
{

class Sprinklers : public IDevice
{
public:
    Sprinklers() = default;
    ~Sprinklers() = default;
    Sprinklers(const Sprinklers & a_sprinklers) = default;
    Sprinklers & operator = (const Sprinklers & a_sprinklers) = default;

    virtual void Work(SharedPointer<IEvent> a_ievent);

};


} // namespace smarthome

#endif // SPRINKLERS_H