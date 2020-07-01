#include "IndexByWord.hpp"

#include <sstream>
#include <algorithm>    // std::set_intersection

namespace cpp
{

void IndexByWord::Insert(Book* a_book)
{

	std::stringstream title(a_book->GetTitle());
	std::string word;
	
	while(title >> word)
	{
		m_indexWord[word].insert(a_book);
	}	   
}

void IndexByWord::Find(std::set<Book*>& a_books, const std::string& a_words)
{
	std::stringstream words(a_words);
	std::string word;
	std::set<Book*> tmpBooks;
	size_t numWords = 0;
	
	while(words >> word)
	{
		std::map<std::string, std::set<Book*> >::iterator iter;	
		iter = m_indexWord.find(word);
		
		if (iter != m_indexWord.end())
		{
			if (numWords)
			{
				if(numWords >= 2)
				{
					tmpBooks = a_books;
				}
				++numWords;
				std::set_intersection(tmpBooks.begin(), tmpBooks.end(), iter->second.begin(), iter->second.end(),std::inserter(a_books,a_books.begin()));
			}
			else
			{
				++numWords;
				tmpBooks = iter->second;
			}
		}
		else
		{
			a_books.clear();
			return;
		}					
	}
	if(1 == numWords)
	{
		a_books = tmpBooks;
	}
}

}
