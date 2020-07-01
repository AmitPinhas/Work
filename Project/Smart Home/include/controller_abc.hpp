#ifndef CONTROLLER_ABC_H
#define CONTROLLER_ABC_H

#include "i_task.hpp"
#include "topic.hpp"

namespace smarthome
{

class ControllerAbc : public advcpp::ITask
{
public:
    explicit ControllerAbc(const Topic & a_topic);
    ~ControllerAbc();

    void ChangeTopic(const Topic & a_topic);
    virtual void Run() = 0;

private:
    Topic m_topic; 
};

inline ControllerAbc::ControllerAbc(const Topic & a_topic)
: m_topic(a_topic)
{
}

inline ControllerAbc::~ControllerAbc()
{
}

inline void ControllerAbc::ChangeTopic(const Topic & a_topic)
{
    m_topic = a_topic;
}


} // namespace smarthome

#endif // CONTROLLER_ABC_H