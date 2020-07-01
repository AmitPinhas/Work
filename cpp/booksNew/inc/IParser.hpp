#ifndef I_PARSER_HPP
#define I_PARSER_HPP

#include <vector>
#include <string>
#include "SuperParser.hpp"

namespace cpp
{

class IParser : public SuperParser
{
public:
	// IParser() = abstract
	// IParser(const IParser& a_other) = abstract
	// IParser& operator=(const IParser& a_other) = abstract
	
	virtual ~IParser() = 0;
	
	virtual void Delim(const std::string& a_line, std::vector<std::string>& a_vector) = 0;
};

}

#endif // I_PARSER_HPP
