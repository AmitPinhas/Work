#include "BookCreator.hpp"

namespace cpp
{

const Book& BookCreator::Creat(const std::vector<std::string>& a_book)
{
	const Author author& = InsertAuthor(a_book[2]);
	const Publisher publisher& = InsertPublisher(a_book[4]);
	Book *book = new Book(a_book[0], a_book[1], a_book[3], author, publisher);
	return *book;
}

}
