#include "util.hpp"

namespace cpp
{

static std::string::iterator UtilClearAllSpacesAtStart(std::string &a_str);
static void UtilClearAllSpacesAtEnd(std::string &a_str);

void UtilClearStringFromSpaces(std::string &a_str)
{
	std::string::iterator it = a_str.begin();
	std::string::iterator end = a_str.end();
	it = UtilClearAllSpacesAtStart(a_str);
	while(it != end && it + 1 != end)
	{
		if(' ' == *it && ' ' == *(it + 1))
		{
			it = a_str.erase(it);
		}
		else
		{
			++it;
		}
	}

	UtilClearAllSpacesAtEnd(a_str);
}

static std::string::iterator UtilClearAllSpacesAtStart(std::string &a_str)
{
	std::string::iterator it = a_str.begin();
	std::string::iterator end = a_str.end();
	while(*it == ' ' && it != end)
	{
		it = a_str.erase(it);
		++it;
	}

	return it;
}

static void UtilClearAllSpacesAtEnd(std::string &a_str)
{
	std::string::iterator end = a_str.begin();
	std::string::iterator it = a_str.end();
	--it;
	while(*it == ' ' && it != end)
	{
		it = a_str.erase(it);
		--it;
	}
}

}


