#include "Library.hpp"

#include <sstream>


namespace cpp
{

void Library::Loader(FileReader& a_fileReader)
{
	a_fileReader.Read();
	
	while(a_fileReader.HasMore())
	{
		std::pair<std::set<Book::Author*>::iterator,bool> retAuthor;
		std::pair<std::set<Book::Publisher*>::iterator,bool> retPublisher;		
		std::string book = a_fileReader.Read();
		
		Parser parser;
		
		Book::Isbn isbnBook = parser.ParsIsbn(book);
		Book::Title titleBook = parser.ParsTitle(book);
		Book::Year yearBook = parser.ParsYear(book);
		Book::Author *authorBook = new Book::Author(parser.ParsAuthor(book));
		Book::Publisher *publisher = new Book::Publisher (parser.ParsPublisher(book));	
		
		retAuthor = m_authors.insert(authorBook);
		retPublisher = m_publishers.insert(publisher);
		
		Book newBook(isbnBook, titleBook, yearBook, *(retAuthor.first), *(retPublisher.first));
		
		m_books.insert ( std::pair<Book::Isbn,Book>(isbnBook,newBook) );
		
	}
	
}

void Library::InsertWords(Book::Title a_title,const Book* a_book)
{
	std::stringstream copyTitle(a_title);
	std::string word;

	while(copyTitle >> word))
	{
		
	}	
		
}	

void Library::FindByIsbn(Book::Isbn a_isbn) const
{
	std::cout << m_books.find(a_isbn)->second << '\n' ;
}

}
