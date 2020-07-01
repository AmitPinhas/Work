#ifndef SUPER_TEXT_READER__HPP
#define SUPER_TEXT_READER__HPP

namespace cpp
{

class SuperTextReader
{
public:
	virtual ~SuperTextReader() = 0;	
	SuperTextReader();	

private:
	SuperTextReader& operator=(const SuperTextReader& a_other);
	SuperTextReader(const SuperTextReader& a_other);
};

}

#endif // SUPER_TEXT_READER__HPP
