#include <iostream>
#include <string>
#include <fstream>      // std::ifstream
#include <sstream>
#include "IReader.hpp" 


//typedef MAX_LINE_LEN 256; //line 52, 53

const static int MAX_LINE = 256;

namespace cpp
{

IReader::~IReader()
{
}

StringReader::StringReader(std::string const& a_str)
: m_str(a_str)
{

}

std::string& StringReader::Read()
{
    return m_str;
}

bool StringReader::IsEnd() const 
{
    return true;
}

//////file reader 

FileReader::FileReader(std::string const& a_str)
: m_fileName(a_str)
, m_str()
, m_fs()
{
}

FileReader::~FileReader()
{
    if (m_fs.is_open() )
    {
        m_fs.close();
    }
}
FileReader::FileReader(FileReader const& a_lhs)
: m_fileName(a_lhs.m_fileName)
, m_str()
, m_fs()
{
}



void FileReader::Open()
{
    if (!m_fs.is_open() )
    {
        m_fs.open(&(m_fileName[0]), std::ifstream::in);
    }
}

void FileReader::Close()
{
    if (m_fs.is_open() )
    {
        
        m_fs.close();
    }
}

std::string& FileReader::Read()
{
    char temp[MAX_LINE];
    m_fs.getline(temp , MAX_LINE, '\n');
    m_str = temp;
    return m_str;
}


bool FileReader::IsEnd() const 
{
    return m_fs.eof() ;
}


////// ConsoleReader funcs
ConsoleReader::ConsoleReader()
: m_str()
{
}

std::string& ConsoleReader::Read()
{
    getline (std::cin, m_str);
    return m_str;
}

bool ConsoleReader::IsEnd() const 
{
    return true;
}

}// end of namespace: cpp