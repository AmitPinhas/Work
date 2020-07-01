#ifndef BOOK_CREATOR_HPP
#define BOOK_CREATOR_HPP

#include <vector>
#include "Book.hpp"

namespace cpp
{

class BookCreator
{
public:
	// BookCreator() = default
	// ~BookCreator() = default
	// BookCreator(const BookCreator& a_other) = default
	// const BookCreator& operator=(const BookCreator& a_other) = default
	
	 Book* Create(const std::vector<std::string>& a_book); 
};

}

#endif // BOOK_CREATOR_HPP
