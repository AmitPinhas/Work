#include "point.hpp"

cpp::Point::Point(int a_x, int a_y)
: m_x(a_x)
, m_y(a_y)
{
}

int& cpp::Point::X() 
{
	return m_x;
}

int& cpp::Point::Y() 
{
	return m_y;
}

const int& cpp::Point::X() const
{
	return m_x;	
}

const int& cpp::Point::Y() const
{
	return m_y;
}
