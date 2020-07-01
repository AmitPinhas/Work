#include "mu_test.h"

#include <string>
#include <iostream>

#include "base_text.hpp"



UNIT(UpperCase_LowerCase)

	std::stringstream myStr;
	
	myStr << "aaa";
	myStr << " bbb" << " llll ";

	std::cout << myStr.str() << '\n';
		
	cpp::BaseText<> aaa(myStr);
	
	std::cout << myStr.str() << '\n';
	
	aaa.UpperCase();
	
	std::cout << myStr.str() << '\n';
	
	aaa.LowerCase();	
	
	std::cout << myStr.str() << '\n';
	
	ASSERT_PASS();

END_UNIT

TEST_SUITE(test the manipulator on fire)

	TEST(UpperCase_LowerCase)

END_SUITE
