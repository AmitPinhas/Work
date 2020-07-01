#ifndef CAMERA_EVENT_HPP
#define CAMERA_EVENT_HPP

#include <string>
#include "event_base.hpp"

namespace smarthome
{

class CameraEvent: public EventBase
{
public:
    CameraEvent(const Topic & a_topic, const TimeStamp & a_timestamp,  const std::string & a_name);
    ~CameraEvent() noexcept = default;
    CameraEvent(const CameraEvent & a_cameraEvent) = default;
    CameraEvent & operator = (const CameraEvent & a_cameraEvent) = default;

    //Flames GetFlames() const;
private:
    std::string m_name;
};

}

#endif //camera_event.hpp