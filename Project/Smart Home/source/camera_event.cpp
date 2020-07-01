#include "camera_event.hpp"

namespace smarthome
{

CameraEvent::CameraEvent(const Topic & a_topic,
             const TimeStamp & a_timestamp,  const std::string & a_name)
: EventBase(a_topic, a_timestamp)
, m_name(a_name)
{
}


}