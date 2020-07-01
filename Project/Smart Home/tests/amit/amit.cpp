#include "mu_test.h"

#include <vector>
#include "shared_pointer.hpp"
#include "i_agent.hpp"
#include "event_structs.hpp"
#include "fire_sensor.hpp"
#include "sprinkler_controller.hpp"
#include "agent_container.hpp"
#include "subscribers_storage.hpp"
#include "broadcast.hpp"
#include "events_queue.hpp"
#include "connector.hpp"
#include "receiver.hpp"
#include "event_dispatcher.hpp"
#include "i_system_api.hpp"
#include "i_subscribers_list_notifier.hpp"

using namespace std;
using namespace advcpp;
using namespace smarthome;

class BroadcastTest : public ISubscribersListNotifier
{
public:

    BroadcastTest();

    virtual void Notifi(SharedPointer<IEvent> a_event);
    virtual void ShutDown();

private:
    size_t m_num;

};

BroadcastTest::BroadcastTest()
: m_num(0)
{ 
}

void BroadcastTest::ShutDown()
{
}

void BroadcastTest::Notifi(SharedPointer<IEvent> )
{
    std::cout << "event number : " << ++m_num << std::endl;
}

class SubscribrFormTest : public ISystemConnectApi
{
public:
    SubscribrFormTest(SharedPointer<IEventReceiver> a_receviver);

    virtual SharedPointer<IEventReceiver> GetReciver();

    virtual void Subscribe(const Topic & a_topic, SharedPointer<ISubscriber> a_subscriber);

private:
    SharedPointer<IEventReceiver> m_receviver;

};

SubscribrFormTest::SubscribrFormTest(SharedPointer<IEventReceiver> a_receviver)
: m_receviver(a_receviver)
{
}

void SubscribrFormTest::Subscribe(const Topic & , SharedPointer<ISubscriber> )
{
}

SharedPointer<IEventReceiver> SubscribrFormTest::GetReciver()
{
    return m_receviver;
}

void Factory(std::vector<SharedPointer<IAgent> > & a_agents, size_t numOfTopics, vector<SharedPointer<FireSensor> >& a_sensors)
{
	
    Location location;
    location.m_floor = 4;
    location.m_room = 1;	
    size_t numEvents = 1;

    size_t numControllers = numOfTopics;

    while(numControllers-- >0)
    {
        SharedPointer<SprinklerController> fireController(new SprinklerController(location));
        fireController->SetSharedPointer(fireController);
        a_agents.push_back(fireController);
    }

    size_t numSensors = numOfTopics;

    while(numSensors-- >0)
    {
        SharedPointer<FireSensor> fireSensor(new FireSensor(location, numEvents));
        a_agents.push_back(fireSensor);
        a_sensors.push_back(fireSensor);
    }
}

UNIT(connect_everyone_test_big_number)

	// AgentContainer agentVector;

    // vector<SharedPointer<FireSensor> > fireSensors;

	// Factory(agentVector.GetStorage(), 1, fireSensors);

	// SharedPointer<SubscribersStorage> sStorage(new SubscribersStorage);
	
	// Broadcast bcast(*sStorage);
	
	// EventsQueue eventsStorage(1000);

    // const size_t numThreads = 1;

    // EventDispatcher eventDispatcher(eventsStorage, bcast, numThreads);

   	// SharedPointer<Receiver> receiver(new Receiver(eventsStorage));
	
	// Connector ConnectEveryone(receiver, sStorage);
	
	// ConnectEveryone.Connect(agentVector);

    // eventDispatcher.Resume();
	
	// eventDispatcher.ShutDown();
	// bcast.ShutDown();

	// ASSERT_PASS();
END_UNIT

UNIT(only_receiver)


    BroadcastTest btest;

    const size_t capacityEventSrotage = 1000;

	EventsQueue eventsStorage(capacityEventSrotage);

    const size_t numThreads = 5;

    EventDispatcher eventDispatcher(eventsStorage, btest, numThreads);

   	SharedPointer<Receiver> receiver(new Receiver(eventsStorage));

    SharedPointer<SubscribrFormTest> subscribeForm(new SubscribrFormTest(receiver));

    Location location;
    location.m_floor = 4;
    location.m_room = 1;	
    size_t numEvents = 300;

    size_t numSensors = 1;

    vector<SharedPointer<FireSensor> > sensors;

    while(numSensors-- >0)
    {
        SharedPointer<FireSensor> fireSensor(new FireSensor(location, numEvents));
        fireSensor->Connect(subscribeForm);
        sensors.push_back(fireSensor);
    }

    eventDispatcher.Resume();

    eventDispatcher.ShutDown();

    ASSERT_PASS();

END_UNIT

TEST_SUITE(amit_test)

    IGNORE_TEST(connect_everyone_test_big_number)
    TEST(only_receiver)

END_SUITE
