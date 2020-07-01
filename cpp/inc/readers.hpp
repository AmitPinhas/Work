#ifndef READERS_HPP
#define READERS_HPP

#include "i_input_text.hpp"

namespace input
{

class StringReader : public cpp::IInputText
{
public:
	explicit StringReader(const std::string& a_string); 
	
	// ~StringWritter() = default
	// StringWritter(const StringWritter& a_other) = default
	// StringWritter& operator=(const StringWritter& a_other) = default
	
	virtual std::string Read() const;
	
private:
	const std::string& String() const;	
	
private:
	const std::string& m_string;	
};

class ConsoleReader : public cpp::IInputText
{
public:
	
	// ConsoleReader() = default 
	// ~ConsoleReader() = default
	// ConsoleReader(const ConsoleReader& a_other) = default
	// ConsoleReader& operator=(const ConsoleReader& a_other) = default
	
	virtual std::string Read() const;
};

class FileReader : public cpp::IInputText
{
public:
	explicit FileReader(const char *a_fileName); 
	
	// ~FileReader() = default
	// FileReader(const FileReader& a_other) = default
	// FileReader& operator=(const FileReader& a_other) = default
	
	virtual std::string Read() const;
	
private:
	const char* FileName() const;	
	std::string FileToString() const;
	
private:
	const char *m_fileName;	
};

}

#endif // READERS_HPP
