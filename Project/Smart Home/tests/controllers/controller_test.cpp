#include "mu_test.h"

#include <iostream>
#include "fire_controller.hpp"
#include "broadcast.hpp"
#include "listener.hpp"
#include "sensor_fire.hpp"

using namespace advcpp;
using namespace smarthome;
using namespace std;
using namespace std::chrono;


UNIT(base_test) 
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << "time: " << ctime(&end_time) << '\n';
	ASSERT_PASS();
END_UNIT

UNIT(base_test_second) 
    Sprinkler sprink;
    sprink.m_id = 1;
    sprink.m_state = Sprinkler::OFF;
    Topic firetopic;
    Location area;
    area.m_floor = 1;
    area.m_room = 1;
    auto end = std::chrono::system_clock::now();
    firetopic.m_time.m_time = std::chrono::system_clock::to_time_t(end);
	firetopic.m_type.m_type = "fire";
	firetopic.m_location = area;
	firetopic.m_payLoad.m_payload = "test";
    
    vector<SharedPointer<IController> > ControllerContainer;
    SharedPointer<IController> sharedController(new SprinklerController(sprink));
    ControllerContainer.push_back(sharedController);
    map<Topic, vector<SharedPointer<IController> > > controllerMap;
    controllerMap[firetopic] = ControllerContainer;
    Broadcast bcast(controllerMap);
    Listener lis(bcast);
    SensorFire sFire(lis, area);
    sFire.SendTopic();
    bcast.ShutDown();


	ASSERT_PASS();
END_UNIT
using namespace std::chrono;
int64_t timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();


TEST_SUITE(flow tests)
	TEST(base_test)
    TEST(base_test_second) 
END_SUITE

