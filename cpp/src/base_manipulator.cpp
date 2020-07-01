#include <locale> // isalpha
#include <cstdio>
#include <cctype>
#include <iostream>
#include "base_manipulator.hpp"
#include <string>

namespace cpp
{

void cpp::BaseManipulator::UpperCase(std::string& a_string)
{
	std::string::iterator begin = a_string.begin();
	std::string::iterator end = a_string.end();
	
	std::locale loc;
	
	while(begin != end)
	{
		*begin = toupper(*begin);
		++begin;
	}
}

void cpp::BaseManipulator::LowerCase(std::string& a_string)
{
	std::string::iterator begin = a_string.begin();
	std::string::iterator end = a_string.end();
	
	std::locale loc;
	
	while(begin != end)
	{
		*begin = tolower(*begin);
		++begin;
	}
}

}
