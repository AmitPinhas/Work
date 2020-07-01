#ifndef BASE_MANIPULATOR_HPP
#define BASE_MANIPULATOR_HPP

#include <string>

#include "manipulator.hpp"

namespace cpp
{
class BaseManipulator : public Manipulator
{
public:	
	// Manipulator(const Manipulator & a_other) = default
	// Manipulator& operator=(const Manipulator & a_other) = default
	// ~Manipulator() = default
	
	virtual void UpperCase(std::string& a_string);
	virtual void LowerCase(std::string& a_string);

};
}

#endif // BASE_MANIPULATOR_HPP
