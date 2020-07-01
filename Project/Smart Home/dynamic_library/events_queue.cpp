#include "events_queue.hpp"

namespace smarthome
{

EventsQueue::EventsQueue(size_t a_capacity)
: m_events(a_capacity)
{
}

} // namespace smarthome