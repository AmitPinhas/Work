#ifndef I_INPUT_TEXT_HPP
#define I_INPUT_TEXT_HPP

#include <iostream>
#include <string>

namespace cpp
{

class IInputText
{
public:
	// IInputText() = delete
	// IInputText(const IInputText& a_other) = delete
	// IInputText& operator=(const IInputText& a_other) = delete
	
	virtual ~IInputText() = 0;
	
	virtual std::string Read() = 0;
};

}

#endif // I_INPUT_TEXT_HPP
