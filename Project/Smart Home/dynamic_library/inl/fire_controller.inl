

#include <chrono> // use time functions for printing
#include <iostream>

namespace smarthome
{

inline SprinklerController::SprinklerController(Sprinkler & a_sprinkler)
: m_sprinkler(a_sprinkler)
{
}

inline void SprinklerController::Run(const Topic & a_topic)
{
    {
        Guard guard(m_mutex);
        std::cout << "time: " << ctime(&a_topic.m_time.m_time) << '\n';
        m_sprinkler.m_state = Sprinkler::ON;
        std::cout << "a_topic: " << a_topic.m_type.m_type << '\n';
        std::cout << "sprinkler: " << m_sprinkler.m_id << "is ON\n";
    }
}


} // namespaec smart_home
