#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>

namespace cpp
{
class Book
{
public:
	typedef std::string Isbn;
	typedef std::string Title;
	typedef std::string Year;
	typedef std::string Author;
	typedef std::string	Publisher;
	
	Book(Isbn a_isbn, Title a_title, Year a_year, const Author* a_author, const Publisher* a_publisher);
	
	const Isbn& GetIsbn() const;
	const Title& GetTitle() const;
	const Year& GetYear() const;
	const Author& GetAuthor() const;
	const Publisher& GetPublisher() const;				
	
	std::ostream& Print(std::ostream& a_os) const;
	
private:
	Isbn m_isbn;
	Title m_title;
	Year m_year;
	const Author* m_author;
	const Publisher* m_publisher;	 		 	
};

std::ostream& operator<<(std::ostream& a_os, const Book& a_book);

}

#endif // BOOK_HPP
