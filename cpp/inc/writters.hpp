#ifndef WRITTERS_HPP
#define WRITTERS_HPP

#include "i_output_text.hpp"

namespace output
{

class StringWritter : public cpp::IOutputText
{
public:
	explicit StringWritter(const std::string& a_string); 
	
	// ~StringWritter() = default
	// StringWritter(const StringWritter& a_other) = default
	// StringWritter& operator=(const StringWritter& a_other) = default
	
	virtual void Write(const std::string& a_string);
	const std::string& String() const;	
	
private:
	std::string m_string;	
};


class ConsoleWritter : public cpp::IOutputText
{
public:
	
    // ConsoleWritter() = default 
	// ~ConsoleWritter() = default
	// ConsoleWritter(const ConsoleWritter& a_other) = default
	// ConsoleWritter& operator=(const ConsoleWritter& a_other) = default
	
	virtual void Write(const std::string& a_string);	
};

class FileWritter : public cpp::IOutputText
{
public:
	explicit FileWritter(const char *a_fileName); 
	
	// ~FileWritter() = default
	// FileWritter(const FileWritter& a_other) = default
	// FileWritter& operator=(const FileWritter& a_other) = default
	
	virtual void Write(const std::string& a_string);
	const char* FileName() const;	
	
private:
	const char *m_fileName;
};

}

#endif // WRITTERS_HPP
