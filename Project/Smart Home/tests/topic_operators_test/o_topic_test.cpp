#include "mu_test.h"

#include <unistd.h>
#include <vector>
#include "event_structs.hpp"

using namespace smarthome;


UNIT(location_test)	
	Location largeRoom;
	largeRoom.m_room = 10;
	largeRoom.m_floor = 1;
	Location smallRoom;
	smallRoom.m_room = 9;
	smallRoom.m_floor = 1;
	ASSERT_THAT(largeRoom > smallRoom);
	ASSERT_THAT(smallRoom < largeRoom);
	ASSERT_THAT(!(smallRoom == largeRoom));
	ASSERT_THAT(smallRoom != largeRoom);

	Location largeFloor;
	largeFloor.m_room = 100;
	largeFloor.m_floor = 2;
	Location smallFloor;
	smallFloor.m_room = 100;
	smallFloor.m_floor = 1;
	ASSERT_THAT(largeFloor > smallFloor);
	ASSERT_THAT(smallFloor < largeFloor);
	ASSERT_THAT(!(smallFloor == largeFloor));
	ASSERT_THAT(smallFloor != largeFloor);

END_UNIT

UNIT(topic_test)	
	Location largeRoom;
	largeRoom.m_room = 10;
	largeRoom.m_floor = 1;
	Topic largeTopic;
	Topic smallTopic;
	largeTopic.m_type.m_type = "zzzzequal";
	smallTopic.m_type.m_type = "azzzz";
	largeTopic.m_location = largeRoom;
	smallTopic.m_location = largeRoom;

	ASSERT_THAT(largeTopic > smallTopic);

END_UNIT

UNIT(topic_location_test)	
	Location largeRoom;
	largeRoom.m_room = 10;
	largeRoom.m_floor = 1;
	Location smallRoom;
	smallRoom.m_room = 9;
	smallRoom.m_floor = 1;

	Topic largeTopic;
	Topic smallTopic;
	largeTopic.m_type.m_type = "equal";
	smallTopic.m_type.m_type = "equal";
	largeTopic.m_location = largeRoom;
	smallTopic.m_location = smallRoom;

	ASSERT_THAT(largeTopic > smallTopic);

END_UNIT

TEST_SUITE(sensor_hub_tests)
	TEST(location_test)
	TEST(topic_test)
	TEST(topic_location_test)		
    
END_SUITE