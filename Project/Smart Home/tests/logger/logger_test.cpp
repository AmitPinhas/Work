#include "mu_test.h"

#include <iostream>
#include "hub_logger.hpp"

using namespace advcpp;
using namespace smarthome;
using namespace std;


UNIT(base_test) 
    // Mutex mutex;
	// HubLogger loggi("logginfortest.txt", mutex);
	// loggi.Log("wow");

	// loggi.Log(12);
	

	ASSERT_PASS();
END_UNIT


UNIT(operator_test) 
    fstream os;
	string str;
	os << 23 << " fstream:" << endl;
	//cout << os << endl;
	
	while(os)
	{
		getline(os, str);
		
	}
	
	cout << str;
	ASSERT_PASS();
END_UNIT


TEST_SUITE(logger tests)
	TEST(base_test)
	TEST(operator_test) 
	
END_SUITE

