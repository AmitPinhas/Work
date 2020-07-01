#ifndef I_OUTPUT_TEXT_HPP
#define I_OUTPUT_TEXT_HPP

#include <iostream>
#include <string>

namespace cpp
{

class IOutputText
{
public:
	// IOutputText() = delete
	// IOutputText(const IOutputText& a_other) = delete
	// IOutputText& operator=(const IOutputText& a_other) = delete
	
	virtual ~IOutputText() = 0;
	
	virtual void Write(const std::string& a_string) = 0;
};

}

#endif // I_OUTPUT_TEXT_HPP
