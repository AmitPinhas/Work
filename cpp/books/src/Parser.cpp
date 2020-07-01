#include "Parser.hpp"

namespace cpp
{

Book::Isbn Parser::ParsIsbn(std::string a_book)
{
	std::string isbn;
	std::string::iterator begin = a_book.begin();
	
	while(*begin != '|')
	{
		isbn.push_back(*begin);
		++begin;
	}
	
	return isbn;		
}

Book::Title Parser::ParsTitle(std::string a_book)
{
	std::string title;
	std::string::iterator begin = a_book.begin();

	while(*begin != '|')
	{
		++begin;
	}	
	++begin;
	
	while(*begin != '|')
	{
		title.push_back(*begin);	
		++begin;
	}	
	
	return title;
}

Book::Year Parser::ParsYear(std::string a_book)
{
	std::string year;
	std::string::iterator begin = a_book.begin();	

	size_t i = 3;
	
	while(i-- > 0)
	{
		while(*begin != '|')
		{
		++begin;
		}		
		++begin;
	}
	
	while(*begin != '|')
	{
		year.push_back(*begin);	
		++begin;
	}	
	
	return year;	
}

Book::Author Parser::ParsAuthor(std::string a_book)
{
	std::string author;
	std::string::iterator begin = a_book.begin();

	size_t i = 2;
	
	while(i-- > 0)
	{
		while(*begin != '|')
		{
		++begin;
		}		
		++begin;
	}
	
	while(*begin != '|')
	{
		author.push_back(*begin);	
		++begin;
	}	
	
	return author;	
}

Book::Publisher Parser::ParsPublisher(std::string a_book)
{
	std::string publisher;
	std::string::iterator begin = a_book.begin();
	std::string::iterator end = a_book.end();	

	size_t i = 4;
	
	while(i-- > 0)
	{
		while(*begin != '|')
		{
		++begin;
		}		
		++begin;
	}
	
	while(begin != end)
	{
		publisher.push_back(*begin);	
		++begin;
	}	
	
	return publisher;	
}


}
