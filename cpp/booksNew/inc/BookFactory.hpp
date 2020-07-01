#ifndef BOOK_FACTORY_HPP
#define BOOK_FACTORY_HPP

#include "IParser.hpp"
#include "ITextReader.hpp"
#include "Book.hpp"
#include "BookCreator.hpp"

namespace cpp
{

class BookFactory
{
public:
	BookFactory(IParser& a_parser, ITextReader& a_reader, BookCreator& a_creator);
	
	// ~BookFactory() = default
	// BookFactory& operator=(const ITextReader& a_other) = default
	// BookFactory(const BookFactory& a_other) = default
	
	Book* GetNextBook();
	bool HasMore();
	
private:
	IParser& m_parser;
	ITextReader& m_reader;
	BookCreator& m_creator;	
};

}

#endif // BOOK_FACTORY_HPP
