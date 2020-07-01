#include "mu_test.h"

#include "agent_creator.hpp"
#include "factory_booter.hpp"
#include "creators_container.hpp"
#include "device_loader.hpp"
#include "device_info.hpp"
#include "agent_container.hpp"
#include "agent_creator.hpp"
#include "device_loader.hpp"
#include "event_structs.hpp"
#include "fire_sensor.hpp"
#include "sprinkler_controller.hpp"
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


using namespace smarthome;

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


void fillDeviceInfo(std::vector<SharedPointer<IDeviceInfo> >& a_info)
{
			Location location;
			location.m_floor = 4;
			location.m_room = 1;	
			size_t numEvents = 1;

			Type type;

			type.m_type = "SprinklerController";

			PayLoad payLoad;
			payLoad.m_payload = "gay";

			SharedPointer<IDeviceInfo> DevInfoTwo(new DeviceInfo(type, location, payLoad) );
			a_info.push_back(DevInfoTwo);
			type.m_type = "FireSensor";

			SharedPointer<IDeviceInfo> DevInfo(new DeviceInfo(type, location, payLoad) );
			a_info.push_back(DevInfo);
}

UNIT(mvp_test_before_so)

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


UNIT(smoke_test)
	std::vector<SharedPointer<IDeviceInfo> > containerDeviceInfo;
	fillDeviceInfo(containerDeviceInfo);

	

	AgentContainer agentContainer;

	CreatorsContainer creatorsContainer;
	DeviceLoader deviceLoader(creatorsContainer);
	SharedPointer<AgentCreator> agentCreator (new AgentCreator(deviceLoader, creatorsContainer));
	FactoryBooter fb(agentCreator);

	const size_t capacityEventSrotage = 1000;

	fb.FillAgentContainer(agentContainer.GetStorage(), containerDeviceInfo);


	ASSERT_EQUAL(agentContainer.GetStorage().size(), 2);
	FireSensor* ptr = dynamic_cast<FireSensor*>(   &*(agentContainer.GetStorage())[1] );
	ASSERT_THAT( ptr );

	ASSERT_EQUAL( ptr->Test(), 5 );

	SprinklerController* ptr_sprinkler = dynamic_cast<SprinklerController*>(   &*(agentContainer.GetStorage())[0] );
	ASSERT_THAT( ptr_sprinkler );

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


TEST_SUITE(every day is so wonderfull suddenly it starts to breathe)
	TEST(mvp_test_before_so)
	TEST(smoke_test)		
    
END_SUITE