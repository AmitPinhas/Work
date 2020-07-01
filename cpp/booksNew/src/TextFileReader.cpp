#include <cassert>
#include "TextFileReader.hpp"

namespace cpp
{

TextFileReader::TextFileReader(const std::string& a_fileName)
: m_file(a_fileName.c_str())
, m_line()
{
	assert(m_file.is_open());
}

std::string TextFileReader::Read()
{
	m_line.clear();	
	getline(m_file, m_line);
	return m_line;
}

bool TextFileReader::HasMore() const
{
	return !m_file.eof();	
}

}
