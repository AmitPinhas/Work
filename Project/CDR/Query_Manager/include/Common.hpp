#ifndef COMMON_HPP
#define COMMON_HPP

namespace advcpp
{

class Uncopyable
{
protected:
	Uncopyable() {}
private:
	Uncopyable(Uncopyable const& a_item);
 	Uncopyable& operator= ( Uncopyable const& a_item);

};

}



#endif /*common.hpp*/
