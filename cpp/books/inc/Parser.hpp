#ifndef PARSER_HPP
#define PARSER_HPP

#include "Book.hpp"

#include <string>

namespace cpp
{

class Parser
{
public:
	// Parser() = default	
	// ~Parser() = default
	// Parser(const Parser& a_other) = default
	// Parser& operator=(const Parser& a_other) = default	
	
	Book::Isbn ParsIsbn(std::string a_book);
	Book::Title ParsTitle(std::string a_book);
	Book::Year ParsYear(std::string a_book);
	Book::Author ParsAuthor(std::string a_book);
	Book::Publisher ParsPublisher(std::string a_book);		
};

}

#endif // PARSER_HPP
