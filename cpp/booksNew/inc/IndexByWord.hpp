#ifndef INDEX_BY_WORD_HPP
#define INDEX_BY_WORD_HPP

#include <string>
#include <map>
#include <set>

#include "IIndex.hpp"
#include "Book.hpp"

namespace cpp
{

class IndexByWord : public IIndex
{
public:
	// IndexByWord() = default
	// ~IndexByWord() = default
	// IndexByWord(const IndexByWord& a_other) = default
	// IndexByWord& operator=(const IndexByWord& a_other) = default
	
	virtual void Find(std::set<Book*>& a_books, const std::string& a_words);
	
	virtual void Insert(Book* a_book);
	
private:
	std::map<std::string, std::set<Book*> > m_indexWord;
};
	
}

#endif // INDEX_BY_WORD_HPP
