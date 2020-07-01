#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <string>

namespace cpp
{
class Manipulator
{
public:	
	// Manipulator(const Manipulator & a_other) = delete
	// Manipulator& operator=(const Manipulator & a_other) = delete	
	
	virtual ~Manipulator();	
	
	virtual void UpperCase(std::string& a_string) = 0;
	virtual void LowerCase(std::string& a_string) = 0;

};
}

#endif // MANIPULATOR_HPP
