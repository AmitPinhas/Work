#include <iostream>
#include <string>
#include "RecordParserByDelim.hpp"
#include "TextFileReader.hpp"
#include "Catalog.hpp"
#include "IndexByWord.hpp"

int main()
{
	cpp::Catalog catalog;
	
	cpp::IndexByWord indexByWord;
	
	std::vector<cpp::IIndex*> m_indexes;
	
	m_indexes.push_back(&indexByWord);

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/books-42.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	catalog.Insert(bookFactory, m_indexes);
	
	//std::cout << "please enter\n1 -> isbn\n2-> title\n";
	
	int number = 1;
	
	//std::cin >> number;

while(number)
{	
	std::cout << "please enter\n1 -> isbn\n2 -> title\n0 -> exit\n";
	std::cin >> number;
	switch(number)
	{
		case 1:
		{
				std::cout << "please enter isbn:\n" ;
				std::string myIsbn = "";
				std::cin >> myIsbn;
				cpp::Book::Isbn isbn(myIsbn);
				const cpp::Book& myBook = catalog.FindByIsbn(isbn);
				std::cout << '\n' << myBook << '\n';
				break;
		}	
		case 2:
		{
				std::cout << "please enter title:\n" ;				
				std::string myTitle = "";
				while ((getchar()) != '\n'); 
				std::getline(std::cin,  myTitle);
				std::set<cpp::Book*> returnBooks;
				catalog.Find(returnBooks, myTitle, &indexByWord);

				std::set<cpp::Book*>::iterator iter = returnBooks.begin();
	
				std::cout << '\n';
	
				while(iter != returnBooks.end())
				{
					std::cout << *(*iter) << '\n' ;
					++iter;
				}		
		}																
		default:
				break;
	}
}	
	return 0;
}

