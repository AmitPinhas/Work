#include "Catalog.hpp"
#include "Book.hpp"

namespace cpp
{
/*
Catalog::Catalog(std::vector<IIndex*>& a_indexes)
: m_indexes(a_indexes)
{
}
*/
const Book::Author& Catalog::InsertAuthor(const Book::Author& a_author)
{
	std::pair<std::set<Book::Author>::iterator,bool> retAuthor;
	Book::Author *author = new Book::Author(a_author);
	retAuthor = m_authors.insert(*author);
	return *retAuthor.first;
}

const Book::Publisher& Catalog::InsertPublisher(const Book::Publisher& a_publisher)
{
	std::pair<std::set<Book::Publisher>::iterator,bool> retPublisher;
	Book::Publisher *publisher = new Book::Publisher(a_publisher);
	retPublisher = m_publishers.insert(*publisher);
	return *retPublisher.first;		
}

void Catalog::Insert(BookFactory& a_bookFactory, std::vector<IIndex*>& m_indexes)
{
	while(a_bookFactory.HasMore())
	{
		Book *book = a_bookFactory.GetNextBook();
		if(book != 0)
		{
			m_books.insert ( std::pair<Book::Isbn,Book>((*book).GetIsbn(),*book) );
			for(size_t i = 0; i < m_indexes.size(); ++i)
			{
				m_indexes[i]->Insert(book);
			}
		}
	}
}


const Book& Catalog::FindByIsbn(Book::Isbn a_isbn) const
{
	return m_books.find(a_isbn)->second ;	
}


void Catalog::Find(std::set<Book*>& a_books, const std::string& a_words, IIndex* m_index)
{
	m_index->Find(a_books, a_words);
}


}
