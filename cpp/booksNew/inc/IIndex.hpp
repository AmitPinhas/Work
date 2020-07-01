#ifndef I_INDEX_HPP
#define I_INDEX_HPP

#include <set>
#include "Book.hpp"
#include "SuperIndex.hpp"

namespace cpp
{

class IIndex : public SuperIndex
{
public:
	// IIndex() = abstract
	// IIndex(const IIndex& a_other) = abstract
	// IIndex& operator=(const IIndex& a_other) = abstract
	
	virtual ~IIndex() = 0;
	
	virtual void Find(std::set<Book*>& a_books, const std::string& a_words) = 0;
	
	virtual void Insert(Book* a_book) = 0;	
};

}

#endif // I_INDEX_HPP
