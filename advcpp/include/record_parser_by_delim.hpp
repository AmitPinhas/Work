#ifndef RECORD_PARSER_BY_DELIM_HPP
#define RECORD_PARSER_BY_DELIM_HPP

#include "i_parser.hpp"

namespace advcpp
{

typedef std::string::const_iterator ConstIterString;
typedef std::vector<std::string>& VectorRefOfString;
typedef const std::string& constRefStr;

class RecordParserByDelim : public IParser
{
public:
	RecordParserByDelim(char a_sign);

	// ~RecordParserByDelim() = default
	// RecordParserByDelim(const RecordParserByDelim& a_other) = default
	// RecordParserByDelim& operator=(const RecordParserByDelim& a_other) = default
	
	virtual void Delim(constRefStr a_infix, VectorRefOfString a_tokens);		

private:
	void SplitToTokens(ConstIterString& a_begin, ConstIterString& a_end, VectorRefOfString a_tokens); 	
	
private:
	char m_sign;		
};

} // namespace advcpp

#endif // RECORD_PARSER_BY_DELIM_HPP
