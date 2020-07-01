#ifndef I_PARSER_HPP
#define I_PARSER_HPP

#include <vector>
#include <string>
#include "uncopyable_parser.hpp"

namespace advcpp
{

class IParser : public UncopyableParser
{
public:	
	virtual ~IParser() = 0;
	
	virtual void Delim(const std::string& a_infix, std::vector<std::string>& a_tokens) = 0;
};

} // namespace advcpp

#endif // I_PARSER_HPP
