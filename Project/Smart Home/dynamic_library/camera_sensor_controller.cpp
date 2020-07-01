#include "camera_sensor_controller.hpp"
#include "camera_event.hpp"
#include "send_events.hpp"


namespace smarthome
{

CameraSenCntrl::CameraSenCntrl(Location a_location, size_t a_numEvents)
:   m_location(a_location)
,   m_numEvents(a_numEvents)
{
}

SharedPointer<IEvent> CameraSenCntrl::createEvent()
{
    Topic cameraTopic;
    cameraTopic.m_type.m_type = "camera sensor";
    cameraTopic.m_location = m_location;

    TimeStamp timeEvent;
    asctime(gmtime(&(timeEvent.m_time)));

    std::string facePalm ="face palm";

    SharedPointer<IEvent> cameraEvent(new CameraEvent(cameraTopic, timeEvent, facePalm)); 

    return cameraEvent;
}


// void SprinklerController::Connect(SharedPointer<ISubscribeForm> a_subscribeForm)
// {
//     auto sprinklerTopic = createTopic();

//     a_subscribeForm->Subscribe(sprinklerTopic, m_SharedPtrThis);
// }

void CameraSenCntrl::SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis)
{
    m_SharedPtrThis = a_SharedPtrThis;
}

void CameraSenCntrl::Notify(SharedPointer<IEvent> a_event)
{
    std::cout << "event type: "<< a_event->GetTopic().m_type.m_type << " camera on \n";    
}



Topic CameraSenCntrl::createTopic()
{
    Topic cameraTopic;
    cameraTopic.m_type.m_type = "camera sensor";
    cameraTopic.m_location = m_location;

    return cameraTopic;
}

void CameraSenCntrl::Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI)
{
    m_ptrReceiver = a_systemConnectAPI->GetReciver();

    SharedPointer<IEvent> cameraEvent = createEvent();

    auto sprinklerTopic = createTopic();

    a_systemConnectAPI->Subscribe(sprinklerTopic, m_SharedPtrThis);

    Thread threadSendEvents(new SendEvents(cameraEvent, m_numEvents, m_ptrReceiver));

    threadSendEvents.Join();   
}

}
