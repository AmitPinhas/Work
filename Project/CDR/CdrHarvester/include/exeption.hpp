#ifndef EXEPTION_HPP
#define EXEPTION_HPP

#include <stdexcept>
#include <string>

#define NO_EXEPTION throw()
#define THROW1(x) throw(x)
#define THROW2(x, y) throw(x, y)
#define THROW3(x, y, z) throw(x, y, z)

#define XTHROW(x, y) throw x(y, InfoExeption(__FILE__, __FUNCTION__, __LINE__) )


class InfoExeption
{
public:
	InfoExeption(const char* a_fileName, const char* a_funcName, size_t a_lineNum) NO_EXEPTION;

	std::string const& FileName() const NO_EXEPTION;
	std::string const& funcName() const NO_EXEPTION;
	size_t LineNum() const NO_EXEPTION;

private:
	const std::string m_fileName;
	const std::string m_funcName;
	const size_t m_lineNum;
};

inline InfoExeption::InfoExeption(const char* a_fileName, const char* a_funcName, size_t a_lineNum) NO_EXEPTION
: m_fileName(a_fileName)
, m_funcName(a_funcName)
, m_lineNum(a_lineNum)
{
}

inline std::string const& InfoExeption::FileName() const NO_EXEPTION
{
	return m_fileName;
}

inline std::string const& InfoExeption::funcName() const NO_EXEPTION
{
	return m_funcName;
}

inline size_t InfoExeption::LineNum() const NO_EXEPTION
{
	return m_lineNum;
}


//////////////////////

class MyExeption : public std::runtime_error
{
protected:
	MyExeption(const char* a_msg, InfoExeption const& a_info) NO_EXEPTION;
    ~MyExeption() NO_EXEPTION;


public:
	std::string const& FileName() const NO_EXEPTION;
	std::string const& funcName() const NO_EXEPTION;
	size_t LineNum() const NO_EXEPTION;

private:
	const InfoExeption m_info;
};

inline MyExeption::MyExeption(const char* a_msg, InfoExeption const& a_info) NO_EXEPTION
: std::runtime_error(a_msg)
, m_info(a_info)
{
}

inline MyExeption::~MyExeption() NO_EXEPTION
{
}

inline std::string const& MyExeption::FileName() const NO_EXEPTION
{
	return m_info.FileName();
}

inline std::string const& MyExeption::funcName() const NO_EXEPTION
{
	return m_info.funcName();
}

inline size_t MyExeption::LineNum() const NO_EXEPTION
{
	return m_info.LineNum();
}


#endif