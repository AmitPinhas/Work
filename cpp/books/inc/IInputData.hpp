#ifndef I_INPUT_DATA_HPP
#define I_INPUT_DATA_HPP

#include <iostream>
#include <string>

namespace cpp
{

class IInputData
{
public:
	// IInputData() = abstract
	// IInputData(const IInputData& a_other) = abstract
	// IInputData& operator=(const IInputData& a_other) = abstract
	
	virtual ~IInputData() = 0;
	
	virtual std::string Read() = 0;
	
	virtual bool HasMore() const = 0;
};

}

#endif // I_INPUT_DATA_HPP
