#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include "IInputData.hpp"

#include <fstream>	// std::ifstream

namespace cpp
{

class FileReader : public IInputData
{
public:
	explicit FileReader(const char *a_fileBooks);
	
	// ~FileReader() = default
	// FileReader(const FileReader& a_other) = default
	// FileReader& operator=(const FileReader& a_other) = default	
	
	virtual std::string Read();
	
	virtual bool HasMore() const;
	
private:	
	const char* Init(const char *a_fileBooks);
			
private:
	std::ifstream m_fileBooks;		  	
};

















}


#endif // FILE_READER_HPP
