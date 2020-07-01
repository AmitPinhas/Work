#include "mu_test.h"

#include <iostream>
#include <string>
#include "RecordParserByDelim.hpp"
#include "TextFileReader.hpp"
#include "Catalog.hpp"
#include "IndexByWord.hpp"
/*
UNIT(Record_Parser_By_Delim)
	cpp::RecordParserByDelim tmp('|');
	std::string string("464564|hfhtfhft|gdfgfd|aaa|bb");
	std::vector<std::string> vec;
	
	tmp.Delim(string, vec);
	
	ASSERT_EQUAL(vec[0] , "464564");
	ASSERT_EQUAL(vec[1] , "hfhtfhft");
	ASSERT_EQUAL(vec[2] , "gdfgfd");
	ASSERT_EQUAL(vec[3] , "aaa");		
	ASSERT_EQUAL(vec[4] , "bb");
		
	ASSERT_PASS();
	
END_UNIT

UNIT(get_new_book)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/Sample_from_the_dara_file.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	while(bookFactory.HasMore())
	{
		const cpp::Book *book = bookFactory.GetNextBook();
		if (book != 0)
		{
			std::cout << *book << '\n' ;
		}
	}
	
	ASSERT_PASS();

END_UNIT


UNIT(insert_and_find_by_isbn_first_book_small_file)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/Sample_from_the_dara_file.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::Catalog catalog;
	
	catalog.Insert(bookFactory);
	
	cpp::Book::Isbn isbn("195153448");
	
	const cpp::Book& myBook = catalog.FindByIsbn(isbn);
					
	std::cout << myBook << '\n' ;

	ASSERT_PASS();

END_UNIT

UNIT(insert_and_find_by_isbn_mid_book_small_file)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/Sample_from_the_dara_file.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::Catalog catalog;
	
	catalog.Insert(bookFactory);
	
	cpp::Book::Isbn isbn("399135782");
	
	const cpp::Book& myBook = catalog.FindByIsbn(isbn);
					
	std::cout << myBook << '\n' ;

	ASSERT_PASS();

END_UNIT

UNIT(insert_and_find_by_isbn_last_book_small_file)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/Sample_from_the_dara_file.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::Catalog catalog;
	
	catalog.Insert(bookFactory);
	
	cpp::Book::Isbn isbn("399132414");
	
	const cpp::Book& myBook = catalog.FindByIsbn(isbn);
					
	std::cout << myBook << '\n' ;

	ASSERT_PASS();

END_UNIT


UNIT(insert_and_find_by_isbn_mid_book_big_file)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/books-42.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::Catalog catalog;
	
	catalog.Insert(bookFactory);
	
	cpp::Book::Isbn isbn("345417623");
	
	const cpp::Book& myBook = catalog.FindByIsbn(isbn);
					
	std::cout << myBook << '\n' ;

	ASSERT_PASS();

END_UNIT

UNIT(index_by_word_insert_and_find_one_word)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/Sample_from_the_dara_file.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::IndexByWord indexByWord;
	
	bookFactory.GetNextBook();
	
	while(bookFactory.HasMore())
	{
		cpp::Book *book = bookFactory.GetNextBook();
		if (book != 0)
		{
			indexByWord.Insert(book);
		}
	}
	
	std::set<cpp::Book*> returnBooks;
	indexByWord.Find(returnBooks, "The");
	
	std::set<cpp::Book*>::iterator iter = returnBooks.begin();
	
	while(iter != returnBooks.end())
	{
		std::cout << *(*iter) << '\n' ;
		++iter;
	}
	
	
	ASSERT_PASS();

END_UNIT


UNIT(index_by_word_insert_and_find_two_words)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/Sample_from_the_dara_file.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::IndexByWord indexByWord;
	
	bookFactory.GetNextBook();
	
	while(bookFactory.HasMore())
	{
		cpp::Book *book = bookFactory.GetNextBook();
		if (book != 0)
		{
			indexByWord.Insert(book);
		}
	}
	
	std::set<cpp::Book*> returnBooks;
	indexByWord.Find(returnBooks, "The Joy");
	
	std::set<cpp::Book*>::iterator iter = returnBooks.begin();
	
	while(iter != returnBooks.end())
	{
		std::cout << *(*iter) << '\n' ;
		++iter;
	}
	
	
	ASSERT_PASS();

END_UNIT

UNIT(index_by_word_insert_and_find_big_file_one_word)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/books-42.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::IndexByWord indexByWord;
	
	bookFactory.GetNextBook();
	
	while(bookFactory.HasMore())
	{
		cpp::Book *book = bookFactory.GetNextBook();
		if (book != 0)
		{
			indexByWord.Insert(book);
		}
	}
	
	std::set<cpp::Book*> returnBooks;
	indexByWord.Find(returnBooks, "Nights");
	
	std::set<cpp::Book*>::iterator iter = returnBooks.begin();
	
	while(iter != returnBooks.end())
	{
		std::cout << *(*iter) << '\n' ;
		++iter;
	}
	
	
	ASSERT_PASS();

END_UNIT


UNIT(index_by_word_insert_and_find_big_file_two_words)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/books-42.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::IndexByWord indexByWord;
	
	bookFactory.GetNextBook();
	
	while(bookFactory.HasMore())
	{
		cpp::Book *book = bookFactory.GetNextBook();
		if (book != 0)
		{
			indexByWord.Insert(book);
		}
	}
	
	std::set<cpp::Book*> returnBooks;
	indexByWord.Find(returnBooks, "Witchfinder Mystery");
	
	std::set<cpp::Book*>::iterator iter = returnBooks.begin();
	
	while(iter != returnBooks.end())
	{
		std::cout << *(*iter) << '\n' ;
		++iter;
	}
	
	
	ASSERT_PASS();

END_UNIT

UNIT(index_by_word_insert_and_find_big_file_three_words)

	cpp::RecordParserByDelim parser('|');
	cpp::IParser& iparser = parser;
	cpp::TextFileReader reader("../../../../Downloads/books-42.txt");
	cpp::ITextReader& ireader = reader;
	cpp::BookCreator creator;
	cpp::BookFactory bookFactory(iparser, ireader, creator);
	
	cpp::IndexByWord indexByWord;
	
	bookFactory.GetNextBook();
	
	while(bookFactory.HasMore())
	{
		cpp::Book *book = bookFactory.GetNextBook();
		if (book != 0)
		{
			indexByWord.Insert(book);
		}
	}
	
	std::set<cpp::Book*> returnBooks;
	indexByWord.Find(returnBooks, "Visitations From the");
	
	std::set<cpp::Book*>::iterator iter = returnBooks.begin();
	
	while(iter != returnBooks.end())
	{
		std::cout << *(*iter) << '\n' ;
		++iter;
	}
	
	
	ASSERT_PASS();

END_UNIT
*/

UNIT(big_test)

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
	
	cpp::Book::Isbn isbn("195153448");
	
	const cpp::Book& myBook = catalog.FindByIsbn(isbn);
	
	std::cout << "find by isbn 195153448:\n" << myBook << '\n';

	std::set<cpp::Book*> returnBooks;
	
	catalog.Find(returnBooks, "Visitations From the", &indexByWord);

	std::set<cpp::Book*>::iterator iter = returnBooks.begin();
	
	std::cout << "find by Visitations From the:\n";
	
	while(iter != returnBooks.end())
	{
		std::cout << *(*iter) << '\n' ;
		++iter;
	}	

	ASSERT_PASS();

END_UNIT


TEST_SUITE(test the books on fire)
/*
	TEST(Record_Parser_By_Delim)
	TEST(get_new_book)
	TEST(insert_and_find_by_isbn_first_book_small_file)
	TEST(insert_and_find_by_isbn_mid_book_small_file)
	TEST(insert_and_find_by_isbn_last_book_small_file)
	TEST(insert_and_find_by_isbn_mid_book_big_file)
	TEST(index_by_word_insert_and_find_one_word)
	TEST(index_by_word_insert_and_find_two_words)
	TEST(index_by_word_insert_and_find_big_file_one_word)
	TEST(index_by_word_insert_and_find_big_file_two_words)
	TEST(index_by_word_insert_and_find_big_file_three_words)
*/
	TEST(big_test)

END_SUITE
