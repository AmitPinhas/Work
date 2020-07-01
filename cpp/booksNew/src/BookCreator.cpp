#include "BookCreator.hpp"
#include "Catalog.hpp"

namespace cpp
{

Book* BookCreator::Create(const std::vector<std::string>& a_book)
{
	Catalog catalogInsert;
	
	if(a_book.size() > 4)
	{
		const Book::Author *author = new  Book::Author(catalogInsert.InsertAuthor(a_book[2]));
		const Book::Publisher *publisher = new Book::Publisher(catalogInsert.InsertPublisher(a_book[4]));
		Book *book = new Book(a_book[0], a_book[1], a_book[3], author, publisher);
		return book;
	}
	return 0;
}

}
