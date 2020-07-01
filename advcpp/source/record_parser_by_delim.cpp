#include "record_parser_by_delim.hpp"

namespace advcpp
{

RecordParserByDelim::RecordParserByDelim(char a_sign)
: m_sign(a_sign)
{
}

void RecordParserByDelim::Delim(constRefStr a_line, VectorRefOfString a_tokens)
{
	ConstIterString begin = a_line.begin();
	ConstIterString end = a_line.end();	
	
	while(begin != end)
	{
		SplitToTokens(begin, end, a_tokens); 
	}	
}

void RecordParserByDelim::SplitToTokens(ConstIterString& a_begin, ConstIterString& a_end, VectorRefOfString a_tokens)
{
	std::string token;
	
	while(a_begin != a_end && *a_begin != m_sign)
	{
		token.push_back(*a_begin);
		++a_begin;
	}
	
	a_tokens.push_back(token);
	
	if(a_begin != a_end)
	{
		++a_begin;
	}	
}

}
