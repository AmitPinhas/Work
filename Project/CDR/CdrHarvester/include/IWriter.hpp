#ifndef I_WRITER_HPP
#define I_READER_HPP

#include <iostream>
#include <string>
#include <fstream>      // std::ofstream

namespace cpp
{


class IWriter
{
public:
    virtual ~IWriter() = 0;
    virtual void Write(std::string const& a_str)  = 0;
};




class StringWriter : public IWriter
{
public:
    // ~StringWriter(); no need 
    // StringWriter(StringWriter const& a_lhs); no need 
    // operator=(StringWriter const& a_lhs); no need 

    StringWriter(std::string & a_str);
    virtual void Write(std::string const& a_str);

private:
    std::string & m_str;
};



class ConsoleWriter : public IWriter
{
public:
    // ~ConsoleWriter(); no need 
    // ConsoleWriter(ConsoleWriter const& a_lhs); no need 
    // operator=(ConsoleWriter const& a_lhs); no need 
    // ConsoleWriter(); no need 

    virtual void Write(std::string const& a_str);
};

class FileWriter : public IWriter
{
public:
    explicit FileWriter(std::string const& a_fileName);

    ~FileWriter();
    FileWriter(FileWriter const& a_lhs);
    //FileWriter const& operator=(FileWriter const& a_lhs); ??????

    virtual void Write(std::string const& a_str);
    void Open(); 
    void Close(); 

private: 
    std::string const& m_fileName;
    std::ofstream m_fs;
};



}
#endif // I_WRITER_HPP