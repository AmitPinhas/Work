#include <fstream>
#include "writters.hpp"

namespace output
{

StringWritter::StringWritter(const std::string& a_string)
: m_string(a_string) 
{
}

const std::string& StringWritter::String() const
{
	return m_string;
}


void StringWritter::Write(const std::string& a_string)
{
	m_string = a_string;
}

void ConsoleWritter::Write(const std::string& a_string)
{
	std::cout << "the text after transform:\n" << a_string ;
}

FileWritter::FileWritter(const char *a_fileName)
: m_fileName(a_fileName) 
{
}

const char* FileWritter::FileName() const
{
	return m_fileName;
}


void FileWritter::Write(const std::string& a_string)
{
	std::fstream myFile(FileName(),  std::fstream::out);
	
	myFile << a_string;	
	
	myFile.close();	
}

}
