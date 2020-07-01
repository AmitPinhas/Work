#ifndef I_TEXT_READER_HPP
#define I_TEXT_READER_HPP

#include <string>
#include "SuperTextReader.hpp"

namespace cpp
{

class ITextReader : public SuperTextReader
{
public:
	// ITextReader() = abstract
	// ITextReader(const ITextReader& a_other) = abstract
	// ITextReader& operator=(const ITextReader& a_other) = abstract
	
	virtual ~ITextReader() = 0;
	
	virtual std::string Read() = 0;
	
	virtual bool HasMore() const = 0;
};

}

#endif // I_TEXT_READER_HPP
