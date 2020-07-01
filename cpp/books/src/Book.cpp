#include "Book.hpp"

namespace cpp
{

Book::Book(Isbn a_isbn, Title a_title, Year a_year, const Author* a_author, const Publisher* a_publisher)
: m_isbn(a_isbn)
, m_title(a_title)
, m_year(a_year)
, m_author(a_author)
, m_publisher(a_publisher)
{
}


const Book::Isbn& Book::ISBN() const
{
	return m_isbn;
}

Book::Isbn& Book::ISBN()
{
	return m_isbn;
}

std::ostream& Book::Print(std::ostream& a_os) const
{
	a_os << m_isbn << "|";
	a_os << m_title << "|";
	a_os << *m_author << "|";	
	a_os << m_year << "|";
	a_os << *m_publisher << '\n' ;
	return a_os;								
}

std::ostream& operator<<(std::ostream& a_os, const Book& a_book)
{
	return a_book.Print(a_os);
}

}
