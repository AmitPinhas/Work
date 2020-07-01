#ifndef TEXT_FILE_READER_HPP
#define TEXT_FILE_READER_HPP

#include <fstream>	// std::ifstream
#include "ITextReader.hpp"

namespace cpp
{

class TextFileReader : public ITextReader
{
public:
	// ~TextFileReader() = default
	// TextFileReader(const TextFileReader& a_other) = default
	// TextFileReader& operator=(const TextFileReader& a_other) = default
	
	TextFileReader(const std::string& a_fileName);
	
	virtual std::string Read();
	
	virtual bool HasMore() const;	

private:
	std::string& Line();	
	
private:
	std::ifstream m_file;
	std::string m_line;	
};

}

#endif // TEXT_FILE_READER_HPP
