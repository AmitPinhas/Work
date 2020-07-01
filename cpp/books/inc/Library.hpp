#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "FileReader.hpp"
#include "Parser.hpp"

#include <set>
#include <map>

namespace cpp
{

class Library
{
public:
	// Library() = default	
	// ~Library() = default
	// Library(const Library& a_other) = default
	// Library& operator=(const Library& a_other) = default	

	void Loader(FileReader& a_fileReader);
	void FindByIsbn(Book::Isbn a_isbn) const;

private:
	void InsertWords(Book::Title a_title,const Book* a_book);		
	
private:
	std::map<Book::Isbn, Book> m_books;
	std::set<Book::Author*> m_authors;
	std::set<Book::Publisher*> m_publishers;
	std::map<Book::Title, std::set<Book*> > m_words;	
};



}

#endif // LIBRARY_HPP
