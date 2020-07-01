#ifndef CATALOG_HPP
#define CATALOG_HPP

#include <set>
#include <map>
#include "BookFactory.hpp"
#include "IIndex.hpp"

namespace cpp
{

class Catalog
{
public:
	 
	// ~Catalog() = default
	// Catalog(const Catalog& a_catalog) = default
	// Catalog& operator=(const Catalog& a_catalog) = default
	
	void Insert(BookFactory& a_bookFactory, std::vector<IIndex*>& m_indexes);

	const Book& FindByIsbn(Book::Isbn a_isbn) const;
	void Find(std::set<Book*>& a_books, const std::string& a_words, IIndex* m_index);
	
	const Book::Author& InsertAuthor(const Book::Author& a_author);
	const Book::Publisher& InsertPublisher(const Book::Publisher& a_publisher);	
	
private:
	std::map<Book::Isbn,Book> m_books;
	std::set<Book::Author> m_authors;
	std::set<Book::Publisher> m_publishers;	
};

}


#endif // CATALOG_HPP
