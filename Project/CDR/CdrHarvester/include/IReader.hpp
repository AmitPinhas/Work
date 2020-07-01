#ifndef I_READER_HPP
#define I_READER_HPP

#include <iostream>
#include <string>
#include <fstream>      // std::ifstream

namespace cpp
{

class IReader
{
public:
    virtual ~IReader() = 0;

    virtual std::string& Read() = 0;
    virtual bool IsEnd() const  = 0;
};


class StringReader : public IReader
{
public:
    //explicit StringReader(StringReader const& a_lhs); no need 
    //StringReader const& operator=(StringReader const& a_lhs); no need 
    //~StringReader(); no need 

    explicit StringReader(std::string const& a_str);
    
    virtual std::string& Read();

    virtual bool IsEnd() const ;

private:
    std::string m_str;
};

class FileReader : public IReader
{
public:
    explicit FileReader(std::string const& a_str);
    FileReader(FileReader const& a_lhs);
    //FileReader const& operator=(FileReader const& a_lhs); ?????
    ~FileReader();

    
    virtual std::string& Read();
    virtual bool IsEnd() const;

    void Open();
    void Close();

private:
    std::string const& m_fileName;
    std::string m_str;
    std::ifstream m_fs;
};

class ConsoleReader : public IReader
{
public:
    //explicit ConsoleReader(ConsoleReader const& a_lhs); no need 
    //ConsoleReader const& operator=(ConsoleReader const& a_lhs); no need 
    //~ConsoleReader(); no need 

    explicit ConsoleReader();
    virtual std::string& Read();

    virtual bool IsEnd() const ;

private:
    std::string m_str;
};

}
#endif // I_READER_HPP