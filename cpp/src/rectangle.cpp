#include "rectangle.hpp"

cpp::Rectangle::Rectangle(const double a_height, const double m_width)
: m_height(a_height)
, m_width(m_width)
{
}

double cpp::Rectangle::Area() const
{
	return Height() * Width();
}

double cpp::Rectangle::Parimeter() const
{
	return Height() * 2 + Width() * 2;
}

void cpp::Rectangle::Scale(double a_scale)
{
	Height() *= a_scale;
	Width() *= a_scale;
}

void cpp::Rectangle::Location(Point const& a_point)
{
	MyPoint().X() = a_point.X();
	MyPoint().Y() = a_point.Y();	
}

cpp::Point const& cpp::Rectangle::Location() const
{
	return m_point;
}

cpp::Point& cpp::Rectangle::Location()
{
	return m_point;
}

void cpp::Rectangle::Draw() const
{
	std::cout << "height: " << Height() << " width: " << Width() << " point x: " << MyPoint().X() << " point y: " << MyPoint().Y() << '\n' ;	
}

void cpp::Rectangle::Move(int a_x, int a_y)
{
	MyPoint().X() += a_x;
	MyPoint().Y()	+= a_y;	
}

double& cpp::Rectangle::Height() 
{
	return m_height;
}

const double& cpp::Rectangle::Height() const
{
	return m_height;	
}

double& cpp::Rectangle::Width() 
{
	return m_width;
}

const double& cpp::Rectangle::Width() const
{
	return m_width;	
}

cpp::Point& cpp::Rectangle::MyPoint()
{
	return m_point;
}

const cpp::Point& cpp::Rectangle::MyPoint() const
{
	return m_point;
}

