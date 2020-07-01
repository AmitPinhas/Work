#include <iostream>
#include <string>
#include <fstream>      // std::ofstream
#include <cassert>
#include "IWriter.hpp"

namespace cpp
{

IWriter::~IWriter()
{
}

StringWriter::StringWriter(std::string & a_str)
: m_str(a_str)
{
}

void StringWriter::Write(std::string const& a_str)
{
    m_str += a_str; 
}



void ConsoleWriter::Write(std::string const& a_str)
{
    std::cout << a_str; 
}


FileWriter::FileWriter(std::string const& a_fileName)
: m_fileName(a_fileName)
, m_fs()
{
}

FileWriter::~FileWriter()
{
    if (m_fs.is_open())
    {
        m_fs.close();
    }
}


FileWriter::FileWriter(FileWriter const& a_lhs)
:   m_fileName(a_lhs.m_fileName)
,   m_fs()
{
}

void FileWriter::Open()
{
    if (!m_fs.is_open())
    {
        m_fs.open(&(m_fileName[0]), std::ofstream::out);
    }
}

void FileWriter::Close()
{
    if (m_fs.is_open())
    {
        m_fs.close();
    }
}

void FileWriter::Write(std::string const& a_str)
{
    m_fs.write(&a_str[0], a_str.length());
}

}// namespace: cpp end
