#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "time.hpp"

namespace advcpp
{

template <typename T>
std::string NumberToString ( T Number )
{
     std::ostringstream ss;
     ss << Number;
     return ss.str();
}

template <typename T>
T StringToNumber ( std::string num )
{
     std::stringstream ss(num);
     T number;
     ss >> number;
     return number;
}

//////////////////// sleep funcs ////////////////////

inline void Sleep(const Nano & a_nano) NOEXCEPTION
{
     timespec t_spec(a_nano);
     nanosleep(&t_spec, 0);
}

inline void Sleep(const Minute & a_minute) NOEXCEPTION
{
     timespec t_spec(a_minute);
     nanosleep(&t_spec, 0);
}

inline void Sleep(const Second & a_second) NOEXCEPTION
{
     timespec t_spec(a_second);
     nanosleep(&t_spec, 0);
}

//////////////////// Random Generator ////////////////////


struct RandomInt
{
     int limit;
     
     RandomInt(int a_limit);

     int operator() ()const;
};

inline RandomInt::RandomInt(int a_limit)
: limit(a_limit)
{
     srand(time(0));
}

inline int RandomInt::operator() () const
{
     return rand() % limit;
}

//////////////////// int filler ////////////////////

struct IntFiller
{
     int value;
     
     IntFiller(int a_value);

     int operator() ()const;
};

inline IntFiller::IntFiller(int a_value)
: value(a_value)
{
}

inline int IntFiller::operator() () const
{
     return value;
}


//////////////////////////parser split /////////////////////////////////////

inline void Parse(const std::string &s, std::vector<std::string> &elems, char a_delim)
{
    std::stringstream newStr(s);
    std::string item;
    std::string line;
	while(std::getline(newStr, item, a_delim))
	{
		elems.push_back(item);
	}
}



} // namespace advcpp

#endif // UTILS_H
