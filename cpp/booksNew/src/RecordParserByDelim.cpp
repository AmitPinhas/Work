#include "RecordParserByDelim.hpp"

namespace cpp
{

RecordParserByDelim::RecordParserByDelim(char a_sign)
: m_sign(a_sign)
{
}

void RecordParserByDelim::Delim(constRefStr a_line, VectorRefOfString a_book)
{
	ConstIterString begin = a_line.begin();
	ConstIterString end = a_line.end();	
	
	while(begin != end)
	{
		SplitToBook(begin, end, a_book); 
	}	
}

void RecordParserByDelim::SplitToBook(ConstIterString& a_begin, ConstIterString& a_end, VectorRefOfString a_book)
{
	std::string tmp;
	
	while(a_begin != a_end && *a_begin != m_sign)
	{
		tmp.push_back(*a_begin);
		++a_begin;
	}
	
	a_book.push_back(tmp);
	
	if(a_begin != a_end)
	{
		++a_begin;
	}	
}

}
