#ifndef I_INFO_H
#define I_INFO_H
#include <iostream>

namespace advcpp 
{

class IInfo
{
public:
	virtual ~IInfo() = 0;
	//virtual std::string GetInfo() = 0;
	

};

inline IInfo::~IInfo()
{
}

} // namespace advcpp

#endif // I_INFO_H
