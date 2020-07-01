#include "mu_test.h"

#include <iostream>

#include "broadcast.hpp"
#include "sprinklers.hpp"
#include "controller.hpp"
#include "test_events.hpp"
#include "controllers_container.hpp"
#include "event_executer.hpp"
#include "havc.hpp"

using namespace advcpp;
using namespace smarthome;
using namespace std;
using namespace std::chrono;


UNIT(base_test) 
    
	SharedPointer<Sprinklers> spSprink(new Sprinklers);
	Location loc;
	loc.m_room = 1;
	loc.m_floor = 2;
	Controller cont(loc, spSprink);
	Topic eventTopic;
	TimeStamp eventTimeStamp;
	FireEvent fireEvent(eventTopic, eventTimeStamp);
	cont.Run(fireEvent);

	

	ASSERT_PASS();
END_UNIT

UNIT(controller_container_test) 
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

	Topic eventTopic;
	TimeStamp eventTimeStamp;
	FireEvent fireEvent(eventTopic, eventTimeStamp);
	cContainer.Dispatch(fireEvent);

	EventExecuter exec(fireEvent, cContainer);
	exec.Run();


	ASSERT_PASS();
END_UNIT

UNIT(broadcast_test) 
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

	Topic eventTopic;
	TimeStamp eventTimeStamp;
	FireEvent fireEvent(eventTopic, eventTimeStamp);

	map<Topic, ControllersContainer> controllersMap;
	controllersMap[fireEvent.GetTopic()] = cContainer;
	Broadcast bcast(controllersMap);
	bcast.Dispatch(fireEvent);
	bcast.ShutDown();
	ASSERT_PASS();
END_UNIT

UNIT(new_event) 
	SharedPointer<HavcDevice> havc(new HavcDevice);
	Location loc;
	loc.m_room = 1;
	loc.m_floor = 2;
	Controller cont(loc, havc);
	Topic eventTopic;
	TimeStamp eventTimeStamp;
	HavcLevel level;
	level.m_temp = 22;
	level.m_fanPower = 3;
	HavcEvent fireEvent(eventTopic, eventTimeStamp, level);
	cont.Run(fireEvent);

	ASSERT_PASS();
END_UNIT

TEST_SUITE(broadcast flow tests)
	TEST(base_test)
	TEST(controller_container_test) 
    TEST(broadcast_test)
	TEST(new_event) 
END_SUITE

