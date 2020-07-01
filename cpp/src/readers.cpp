#include <fstream>
#include "readers.hpp"


namespace input
{

StringReader::StringReader(const std::string& a_string)
: m_string(a_string) 
{
}

const std::string& StringReader::String() const
{
	return m_string;
}

std::string StringReader::Read() const
{
	return String();
}

std::string ConsoleReader::Read() const
{
	std::cout << "please enter the text:\n" ;
	
	std::string text;
	
	std::getline (std::cin,text);
	
	return text;
}

FileReader::FileReader(const char *a_fileName)
: m_fileName(a_fileName) 
{
}

const char* FileReader::FileName() const
{
	return m_fileName;
}

std::string FileReader::Read() const
{
	return FileToString();
}

std::string FileReader::FileToString() const
{
	std::fstream myFile(FileName(),  std::fstream::in);
	std::string copyFile;
	std::string line;
	
	while(getline(myFile, line))
	{
		copyFile.append(line);
		copyFile.append("\n");		
	}
	myFile.close();
	
	return copyFile;	
}

}
