#ifndef RECORD_PARSER_BY_DELIM_HPP
#define RECORD_PARSER_BY_DELIM_HPP

#include "IParser.hpp"

namespace cpp
{

typedef std::string::const_iterator ConstIterString;
typedef std::vector<std::string>& VectorRefOfString;
typedef const std::string& constRefStr;

class RecordParserByDelim : public IParser
{
public:
	// ~RecordParserByDelim() = default
	// RecordParserByDelim(const RecordParserByDelim& a_other) = default
	// RecordParserByDelim& operator=(const RecordParserByDelim& a_other) = default
	
	RecordParserByDelim(char a_sign);
	
	virtual void Delim(constRefStr a_line, VectorRefOfString a_book);		

private:
	void SplitToBook(ConstIterString& a_begin, ConstIterString& a_end, VectorRefOfString a_book); 	
	
private:
	char m_sign;		
};

}

#endif // RECORD_PARSER_BY_DELIM_HPP
