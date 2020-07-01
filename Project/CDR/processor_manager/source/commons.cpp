#include "commons.hpp"

namespace advcpp
{
       
Nano::operator timespec() const NOEXCEPT
{ 	
    struct timespec req;
	req.tv_nsec = value;
	req.tv_sec = 0;
    return req;
}

Minutes::operator timespec() const NOEXCEPT
{ 
    struct timespec req;
	req.tv_nsec = 0;
	req.tv_sec = value * 60;
    return req;
}





}//namespace advcpp