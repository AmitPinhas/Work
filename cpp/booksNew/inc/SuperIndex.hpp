#ifndef SUPER_INDEX_HPP
#define SUPER_INDEX_HPP

namespace cpp
{

class SuperIndex
{
public:
	virtual ~SuperIndex() = 0;	
	SuperIndex();	

private:
	SuperIndex& operator=(const SuperIndex& a_other);
	SuperIndex(const SuperIndex& a_other);
};

}

#endif // SUPER_INDEX_HPP
