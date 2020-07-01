#include "mu_test.h"

#include <unistd.h>
#include <vector>

#include "fire_sensor.hpp"
#include "sprinkler_controller.hpp"
#include "sensor.hpp"
#include "event_structs.hpp"
#include "receiver.hpp"
#include "events_queue.hpp"
#include "pop_event.hpp"
#include "shared_pointer.hpp"
#include "dequeue_event.hpp"
#include "i_task.hpp"
//#include "broadcast.hpp"
#include "sprinklers.hpp"
#include "controller.hpp"
#include "i_agent.hpp"

using namespace smarthome;
using namespace advcpp;

UNIT(base_test)
/*
	ControllersContainer cContainer;
	SharedPointer<Sprinklers> spSprink(new Sprinklers);
	Location loc;
	loc.m_room = 1;
	loc.m_floor = 2;
	for(size_t i = 0; i < 10; ++i)
	{
		SharedPointer<IController> newptr(new Controller (loc, spSprink));
		cContainer.Add(newptr);
	}

    Topic fireTopic;
    fireTopic.m_type.m_type = "fire";
    fireTopic.m_location.m_floor = 4;
    fireTopic.m_location.m_room = 1;

	map<Topic, ControllersContainer> controllersMap;
	controllersMap[fireTopic] = cContainer;
	Broadcast bcast(controllersMap);

    EventsQueue events(1000);
    SharedPointer<ITask> iTaskPtr(new smarthome::DequeueEvent(events, bcast));
    size_t a_maxTasks = 1000;
    size_t a_numOfThreads = 1;
    PopEvent popEvents(a_maxTasks, a_numOfThreads, iTaskPtr);
    Receiver receiver(events, popEvents);
    Sensor sensorFire(fireTopic, receiver);

	size_t numEvents = 20;
	while(numEvents-- > 0)
	{
    	sensorFire.SendEvent();
	}

	popEvents.ShutDown();
	bcast.ShutDown();
*/
    ASSERT_PASS();
    
END_UNIT

UNIT(test_factory)

	Location location;
    location.m_floor = 4;
    location.m_room = 1;	
	size_t numEvents = 1;

	std::vector<SharedPointer<IAgent> > agents;

	size_t numSensors = 10;

	while(numSensors-- >0)
	{
		SharedPointer<IAgent> fireSensor(new FireSensor(location, numEvents));
		agents.push_back(fireSensor);
	}

	size_t numControllers = 10;

	while(numControllers-- >0)
	{
		SharedPointer<SprinklerController> fireController(new SprinklerController(location));
		fireController->SetSharedPointer(fireController);
		agents.push_back(fireController);
	}	
	
	

	ASSERT_PASS();

END_UNIT

TEST_SUITE(sensor_hub_tests)
	TEST(base_test)
    
END_SUITE