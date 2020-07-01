#include "FileReader.hpp"

#include <cassert>

namespace cpp
{

FileReader::FileReader(const char *a_fileBooks)
: m_fileBooks(Init(a_fileBooks))
{
}

const char* FileReader::Init(const char *a_fileBooks)
{
	assert(a_fileBooks != 0);	
	return a_fileBooks;
}

std::string FileReader::Read()
{
	std::string line;
	
	getline(m_fileBooks, line);
	
	return line;
}


bool FileReader::HasMore() const
{
	return !m_fileBooks.eof();
}

}
