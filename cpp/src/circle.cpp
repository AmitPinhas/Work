#define _USE_MATH_DEFINES
#include <cmath> //M_PI
#include <iostream>
#include "circle.hpp"

cpp::Circle::Circle(double a_radius)
: m_radius(a_radius)
{
}

double cpp::Circle::Circle::Area() const
{
	return M_PI * Radius() * Radius();
}

double cpp::Circle::Parimeter() const
{
	return 2 * M_PI * Radius();
}

void cpp::Circle::Scale(double a_scale)
{
	Radius() *= a_scale;
}

void cpp::Circle::Location(cpp::Point const& a_point)
{
	MyPoint().X() = a_point.X();
	MyPoint().Y() = a_point.Y();
}

cpp::Point const& cpp::Circle::Location() const
{
	return MyPoint();
}

cpp::Point& cpp::Circle::Location()
{
	return MyPoint();	
}

void cpp::Circle::Draw() const
{
	std::cout << "radius: " << m_radius << " point x: " << MyPoint().X() << " point y: " << MyPoint().Y() << '\n' ;
}

void cpp::Circle::Move(int a_x, int a_y)
{
	MyPoint().X() += a_x;
	MyPoint().Y()	+= a_y;
}

double& cpp::Circle::Radius()
{
	return m_radius;
}

const double& cpp::Circle::Radius() const
{
	return m_radius;
}

cpp::Point& cpp::Circle::MyPoint()
{
	return m_point;
}

const cpp::Point& cpp::Circle::MyPoint() const
{
	return m_point;
}
