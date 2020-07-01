#ifndef FIRE_CONTROLLER_H
#define FIRE_CONTROLLER_H

#include "i_controller.hpp" // implementation of IController
#include "mutex.hpp" // safe controller using guard

using namespace advcpp;

namespace smarthome
{

struct Sprinkler
{
    enum STATE {ON, OFF, DAMAGED, END};
    STATE       m_state;
    size_t      m_id;
};


class SprinklerController : public IController
{
public:
    SprinklerController(Sprinkler & a_sprinkler);
    virtual void Run(const Topic & a_topic);

private:
    Sprinkler & m_sprinkler;
    Mutex m_mutex;
};


} // namespace smart_home

#include "inl/fire_controller.inl"

#endif // FIRE_CONTROLLER_H