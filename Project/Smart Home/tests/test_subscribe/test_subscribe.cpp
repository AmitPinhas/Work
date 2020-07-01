#include "mu_test.h"
#include "i_agent_container.hpp"
#include "connector.hpp"
#include "i_agent.hpp"
#include "i_subscriber.hpp"
#include "agent_container.hpp"
#include <map>
#include "camera_sensor_controller.hpp"
#include <typeinfo>


//amit includes
#include "fire_sensor.hpp"
#include "sprinkler_controller.hpp"
#include "sensor.hpp"
#include "event_structs.hpp"
#include "receiver.hpp"
#include "event_dequeuer.hpp"
#include "event_dispatcher.hpp"
#include "shared_pointer.hpp"
//#include "dequeue_event.hpp"
#include "i_task.hpp"
//#include "broadcast.hpp"
#include "sprinklers.hpp"
#include "controller.hpp"
#include "i_agent.hpp"
#include "events_queue.hpp"
#include "i_event_storage_pop.hpp"
#include "i_event_storage_push.hpp"

//yotam includes
#include <iostream>
#include "subscribers_list.hpp"
#include "subscribers_list.hpp"
#include "fire_event.hpp"
#include "subscribers_storage.hpp"
#include "broadcast.hpp"
#include "subscribers_list_notifier.hpp"
#include "empty_controller.hpp"
#include "false_sensor.hpp"
#include "false_fire_controller.hpp"
#include "sprinkler_flame_controller.hpp"

using namespace advcpp;
using namespace smarthome;
using namespace std;

AtomicValue<int> g_atomic(0);

void FactoryCamera(std::vector<SharedPointer<IAgent> > & a_agents, size_t numOfTopics)
{
	
			Location location;
			location.m_floor = 4;
			location.m_room = 1;	
			size_t numEvents = 1;


			size_t numControllers = numOfTopics;

			while(numControllers-- >0)
			{
				SharedPointer<CameraSenCntrl> cameraSensorController(new CameraSenCntrl(location, numEvents));
				cameraSensorController->SetSharedPointer(cameraSensorController);
				a_agents.push_back(cameraSensorController);
			}

			// size_t numSensors = numOfTopics;

			// while(numSensors-- >0)
			// {
			// 	SharedPointer<IAgent> fireSensor(new FireSensor(location, numEvents));
			// 	a_agents.push_back(fireSensor);
			// }
}


void FactoryTwoListener(std::vector<SharedPointer<IAgent> > & a_agents, size_t numOfTopics)
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

			SharedPointer<EmptyController> emptyController(new EmptyController(location));
			emptyController->SetSharedPointer(emptyController);
			a_agents.push_back(emptyController);

			size_t numSensors = numOfTopics;

			while(numSensors-- >0)
			{
				SharedPointer<IAgent> fireSensor(new FireSensor(location, numEvents));
				a_agents.push_back(fireSensor);
			}
}


void FactoryRegular(std::vector<SharedPointer<IAgent> > & a_agents, size_t numOfTopics)
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
				SharedPointer<IAgent> fireSensor(new FireSensor(location, numEvents));
				a_agents.push_back(fireSensor);
			}
}

void FactoryFalse(std::vector<SharedPointer<IAgent> > & a_agents, size_t numOfTopics)
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
				SharedPointer<IAgent> falseSensor(new FalseSensor(location, numEvents));
				a_agents.push_back(falseSensor);
			}
}

void FactoryFireFalse(std::vector<SharedPointer<IAgent> > & a_agents, size_t numOfTopics)
{
	
			Location location;
			location.m_floor = 4;
			location.m_room = 1;	
			size_t numEvents = 1;


			size_t numControllers = numOfTopics;

			while(numControllers-- >0)
			{
				SharedPointer<FalseFireControlller> falseFireController(new FalseFireControlller(location));
				falseFireController->SetSharedPointer(falseFireController);
				a_agents.push_back(falseFireController);
			}

			size_t numSensors = numOfTopics;

			while(numSensors-- >0)
			{
				SharedPointer<IAgent> fireSensor(new FireSensor(location, numEvents));
				SharedPointer<IAgent> falseSensor(new FalseSensor(location, numEvents));
				a_agents.push_back(falseSensor);
				a_agents.push_back(fireSensor);
			}

			
}


void FactoryFireCntrlSensorFalseCntrl(std::vector<SharedPointer<IAgent> > & a_agents, size_t numOfTopics)
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

			SharedPointer<CameraSenCntrl> cameraSensorController(new CameraSenCntrl(location, numEvents));
			cameraSensorController->SetSharedPointer(cameraSensorController);
			a_agents.push_back(cameraSensorController);

			while(numSensors-- >0)
			{
				SharedPointer<IAgent> fireSensor(new FireSensor(location, numEvents));
				a_agents.push_back(fireSensor);
			}
}

void FactoryAtomic(std::vector<SharedPointer<IAgent> > & a_agents, size_t numOfTopics)
{
	
			Location location;
			location.m_floor = 4;
			location.m_room = 1;	
			size_t numEvents = 1;


			size_t numControllers = numOfTopics;

			while(numControllers-- >0)
			{
				SharedPointer<SprinklerFlameController> fireController(new SprinklerFlameController(location, g_atomic));
				fireController->SetSharedPointer(fireController);
				a_agents.push_back(fireController);
			}

			size_t numSensors = numOfTopics;

			while(numSensors-- >0)
			{
				SharedPointer<IAgent> fireSensor(new FireSensor(location, numEvents));
				a_agents.push_back(fireSensor);
			}
}


UNIT(Agent_Container_test)
	//build agent_container
	AgentContainer AgentVector;


	ASSERT_PASS();
END_UNIT

UNIT(factory_fill_test)
	//build agent_container
	//give storage to factory to fill with agents
	AgentContainer AgentVector;
	FactoryCamera(AgentVector.GetStorage(), 10);
	

	ASSERT_PASS();
END_UNIT

UNIT(same_contr_sensor_test)
	//build agent_container
	//give to factory to fill with agent
	// connect everyone with subscribe form

	const size_t capacityEventSrotage = 1000;

	AgentContainer agentContainer;// local variables must be with lower cast  // vitaly

	FactoryCamera(agentContainer.GetStorage(),2); //test needs

	SharedPointer<SubscribersStorage> sStorage(new SubscribersStorage); // yotam 
	
	SubscribersListNotifier bcast(*sStorage); // yotam

	EventsQueue eventsStorage(capacityEventSrotage);

	const size_t numThreads = 1;

	EventDispatcher eventDispatcher(eventsStorage, bcast, numThreads);

	SharedPointer<Receiver> receiver(new Receiver(eventsStorage));

	SharedPointer<SystemConnectApi> api(new SystemConnectApi(receiver, sStorage));

	Connector connector(api);
	
	connector.Connect(agentContainer);
	
	eventDispatcher.Resume();

	eventDispatcher.ShutDown();

	bcast.ShutDown();

	ASSERT_PASS();
END_UNIT

UNIT(test_one_topic_one_listener)
	//build agent_container
	//give to factory to fill with agent
	// connect everyone with subscribe form

	const size_t capacityEventSrotage = 1000;

	AgentContainer agentContainer;// local variables must be with lower cast  // vitaly

	FactoryRegular(agentContainer.GetStorage(),2); //test needs

	SharedPointer<SubscribersStorage> sStorage(new SubscribersStorage); // yotam 
	
	SubscribersListNotifier bcast(*sStorage); // yotam

	EventsQueue eventsStorage(capacityEventSrotage);

	const size_t numThreads = 1;

	EventDispatcher eventDispatcher(eventsStorage, bcast, numThreads);

   	//SharedPointer<ITask> iTaskPtr(new smarthome::DequeueEvent(events, bcast));
   	
	//size_t a_maxTasks = 1000;

   	//size_t a_numOfThreads = 1;

  	//PopEvent popEvents(a_maxTasks, a_numOfThreads, iTaskPtr);

	SharedPointer<Receiver> receiver(new Receiver(eventsStorage));

   	//SharedPointer<IEventReceiver> receiver(new Receiver(events, popEvents));

	SharedPointer<SystemConnectApi> api(new SystemConnectApi(receiver, sStorage));

	Connector connector(api);
	
	connector.Connect(agentContainer);
	
	eventDispatcher.Resume();

	eventDispatcher.ShutDown();

	bcast.ShutDown();

	ASSERT_PASS();
END_UNIT


UNIT(test_contreller_listen_two_topic)
	//build agent_container
	//give to factory to fill with agent
	// connect everyone with subscribe form


	const size_t capacityEventSrotage = 1000;

	AgentContainer agentContainer;// local variables must be with lower cast  // vitaly

	FactoryTwoListener(agentContainer.GetStorage(),2); //test needs

	SharedPointer<SubscribersStorage> sStorage(new SubscribersStorage); // yotam 
	
	SubscribersListNotifier bcast(*sStorage); // yotam

	EventsQueue eventsStorage(capacityEventSrotage);

	const size_t numThreads = 1;

	EventDispatcher eventDispatcher(eventsStorage, bcast, numThreads);

   	//SharedPointer<ITask> iTaskPtr(new smarthome::DequeueEvent(events, bcast));
   	
	//size_t a_maxTasks = 1000;

   	//size_t a_numOfThreads = 1;

  	//PopEvent popEvents(a_maxTasks, a_numOfThreads, iTaskPtr);

	SharedPointer<Receiver> receiver(new Receiver(eventsStorage));

   	//SharedPointer<IEventReceiver> receiver(new Receiver(events, popEvents));

	SharedPointer<SystemConnectApi> api(new SystemConnectApi(receiver, sStorage));

	Connector connector(api);
	
	connector.Connect(agentContainer);
	
	eventDispatcher.Resume();

	eventDispatcher.ShutDown();

	bcast.ShutDown();


	ASSERT_PASS();
END_UNIT

UNIT(test_on_topic_nobody_listen)
	//build agent_container
	//give to factory to fill with agent
	// connect everyone with subscribe form


	const size_t capacityEventSrotage = 1000;

	AgentContainer agentContainer;// local variables must be with lower cast  // vitaly

	FactoryFalse(agentContainer.GetStorage(),100); //test needs

	SharedPointer<SubscribersStorage> sStorage(new SubscribersStorage); // yotam 
	
	SubscribersListNotifier bcast(*sStorage); // yotam

	EventsQueue eventsStorage(capacityEventSrotage);

	const size_t numThreads = 1;

	EventDispatcher eventDispatcher(eventsStorage, bcast, numThreads);

   	//SharedPointer<ITask> iTaskPtr(new smarthome::DequeueEvent(events, bcast));
   	
	//size_t a_maxTasks = 1000;

   	//size_t a_numOfThreads = 1;

  	//PopEvent popEvents(a_maxTasks, a_numOfThreads, iTaskPtr);

	SharedPointer<Receiver> receiver(new Receiver(eventsStorage));

   	//SharedPointer<IEventReceiver> receiver(new Receiver(events, popEvents));

	SharedPointer<SystemConnectApi> api(new SystemConnectApi(receiver, sStorage));

	Connector connector(api);
	
	connector.Connect(agentContainer);
	
	eventDispatcher.Resume();

	eventDispatcher.ShutDown();

	bcast.ShutDown();


	ASSERT_PASS();
END_UNIT

UNIT(test_two_topics_one_listener)
		//build agent_container
	//give to factory to fill with agent
	// connect everyone with subscribe form


	const size_t capacityEventSrotage = 1000;

	AgentContainer agentContainer;// local variables must be with lower cast  // vitaly

	FactoryFireFalse(agentContainer.GetStorage(),10); //test needs

	SharedPointer<SubscribersStorage> sStorage(new SubscribersStorage); // yotam 
	
	SubscribersListNotifier bcast(*sStorage); // yotam

	EventsQueue eventsStorage(capacityEventSrotage);

	const size_t numThreads = 1;

	EventDispatcher eventDispatcher(eventsStorage, bcast, numThreads);

   	//SharedPointer<ITask> iTaskPtr(new smarthome::DequeueEvent(events, bcast));
   	
	//size_t a_maxTasks = 1000;

   	//size_t a_numOfThreads = 1;

  	//PopEvent popEvents(a_maxTasks, a_numOfThreads, iTaskPtr);

	SharedPointer<Receiver> receiver(new Receiver(eventsStorage));

   	//SharedPointer<IEventReceiver> receiver(new Receiver(events, popEvents));

	SharedPointer<SystemConnectApi> api(new SystemConnectApi(receiver, sStorage));

	Connector connector(api);
	
	connector.Connect(agentContainer);
	
	eventDispatcher.Resume();


	eventDispatcher.ShutDown();

	bcast.ShutDown();
	

	for_each(agentContainer.GetStorage().begin(), agentContainer.GetStorage().end(),
			 [](auto agent){ if( dynamic_cast<FalseFireControlller*>(&*agent)  ) 
			 										{   cout<<"dynamic cast---->"<<"+"<<dynamic_cast<FalseFireControlller*>(&*agent)->GetValue()<<"+"<<endl; } }  );


	ASSERT_PASS();

END_UNIT

UNIT(test_on_topic_that_never_occured)
		//build agent_container
	//give to factory to fill with agent
	// connect everyone with subscribe form


	const size_t capacityEventSrotage = 1000;

	AgentContainer agentContainer;// local variables must be with lower cast  // vitaly

	FactoryFireCntrlSensorFalseCntrl(agentContainer.GetStorage(),5); //test needs

	SharedPointer<SubscribersStorage> sStorage(new SubscribersStorage); // yotam 
	
	SubscribersListNotifier bcast(*sStorage); // yotam

	EventsQueue eventsStorage(capacityEventSrotage);

	const size_t numThreads = 1;

	EventDispatcher eventDispatcher(eventsStorage, bcast, numThreads);

   	//SharedPointer<ITask> iTaskPtr(new smarthome::DequeueEvent(events, bcast));
   	
	//size_t a_maxTasks = 1000;

   	//size_t a_numOfThreads = 1;

  	//PopEvent popEvents(a_maxTasks, a_numOfThreads, iTaskPtr);

	SharedPointer<Receiver> receiver(new Receiver(eventsStorage));

   	//SharedPointer<IEventReceiver> receiver(new Receiver(events, popEvents));

	SharedPointer<SystemConnectApi> api(new SystemConnectApi(receiver, sStorage));

	Connector connector(api);
	
	connector.Connect(agentContainer);
	
	eventDispatcher.Resume();

	eventDispatcher.ShutDown();

	bcast.ShutDown();


	ASSERT_PASS();

END_UNIT

UNIT(test_with_atomic)

	const size_t capacityEventSrotage = 1000;

	AgentContainer agentContainer;// local variables must be with lower cast  // vitaly

	FactoryAtomic(agentContainer.GetStorage(),5); //test needs

	SharedPointer<SubscribersStorage> sStorage(new SubscribersStorage); // yotam 
	
	SubscribersListNotifier bcast(*sStorage); // yotam

	EventsQueue eventsStorage(capacityEventSrotage);

	const size_t numThreads = 1;

	EventDispatcher eventDispatcher(eventsStorage, bcast, numThreads);

   	

	SharedPointer<Receiver> receiver(new Receiver(eventsStorage));

   	//SharedPointer<IEventReceiver> receiver(new Receiver(events, popEvents));

	SharedPointer<SystemConnectApi> api(new SystemConnectApi(receiver, sStorage));

	Connector connector(api);
	
	connector.Connect(agentContainer);
	
	eventDispatcher.Resume();

	eventDispatcher.ShutDown();

	bcast.ShutDown();


	ASSERT_EQUAL(g_atomic.Value(), 25);


END_UNIT


TEST_SUITE(subscribe_tests)
	// TEST(Agent_Container_test)
   	// TEST(factory_fill_test)
	// TEST(same_contr_sensor_test)
	// TEST(test_on_topic_nobody_listen)
	// TEST(test_contreller_listen_two_topic)
	// TEST(test_one_topic_one_listener)
	// TEST(test_two_topics_one_listener)
	// TEST(test_on_topic_that_never_occured)
	TEST(test_with_atomic)

END_SUITE
