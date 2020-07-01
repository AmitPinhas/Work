#ifndef UNCOPYABLE_PARSER_HPP
#define UNCOPYABLE_PARSER_HPP

namespace advcpp
{

class UncopyableParser
{
public:
	virtual ~UncopyableParser() = 0;	
	UncopyableParser();	

private:
	UncopyableParser& operator=(const UncopyableParser& a_other);
	UncopyableParser(const UncopyableParser& a_other);
};

} // namespace advcpp

#endif // UNCOPYABLE_PARSER_HPP
