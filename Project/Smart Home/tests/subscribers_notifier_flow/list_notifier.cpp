#include "mu_test.h"

#include <vector>
#include <unistd.h>
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
#include "subscribers_list_notifier.hpp"

using namespace std;
using namespace advcpp;
using namespace smarthome;

class Sprinklers : public ISubscriber
{
public:
    void Notify(SharedPointer<IEvent> a_event){(void)a_event; cout << "sprinkle sprinkle" << endl;}
};

class SprinklersEvent : public IEvent
{
public:
    SprinklersEvent(Topic a_topic): m_topic(a_topic){};
    virtual TimeStamp GetTimeStamp()const {return TimeStamp();};
    virtual Topic GetTopic()const {return m_topic;};

private:
    Topic m_topic;
};

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

	SubscribersStorage sStorage;

    
	Location loc;
	loc.m_room = 1;
	loc.m_floor = 2;
    Type type;
    type.m_type = "sprinkle";
    Topic top;
    top.m_location = loc;
    top.m_type = type;
    SharedPointer<ISubscriber> newptr2(new Sprinklers);
	for(size_t i = 0; i < 4; ++i)
	{
		SharedPointer<ISubscriber> newptr(new Sprinklers);
		sStorage.Subscribe(top, newptr);
        newptr2 = newptr;
	}
	

    SharedPointer<IEvent> sEvent( new SprinklersEvent(top));
	SubscribersListNotifier notifier (sStorage);
    notifier.Notifi(sEvent);
    std::vector<Topic> topics;
    topics.push_back(top);

    sleep(1);
    sStorage.UnSubscribe(topics, newptr2);
    cout << "\n\n" << endl;
    notifier.Notifi(sEvent);
	notifier.ShutDown();

	ASSERT_PASS();
END_UNIT

TEST_SUITE(amit_test)

    TEST(connect_everyone_test_big_number)

END_SUITE