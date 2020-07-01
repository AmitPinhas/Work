#ifndef SUPER_PARSER_HPP
#define SUPER_PARSER_HPP

namespace cpp
{

class SuperParser
{
public:
	virtual ~SuperParser() = 0;	
	SuperParser();	

private:
	SuperParser& operator=(const SuperParser& a_other);
	SuperParser(const SuperParser& a_other);
};

}

#endif // SUPER_PARSER_HPP
