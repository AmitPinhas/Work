#include <iostream>
#include "line.hpp"

cpp::Line::Line(double a_edge)
: m_edge(a_edge)
{
}

double cpp::Line::Area() const
{
	return 0;
}

double cpp::Line::Parimeter() const
{
	return Edge();
}

void cpp::Line::Scale(double a_scale)
{
	Edge() *= a_scale;
}
	
void cpp::Line::Location(cpp::Point const& a_point)
{
	MyPoint().X() = a_point.X();
	MyPoint().Y() = a_point.Y();	
}

cpp::Point const& cpp::Line::Location() const
{
	return MyPoint();
}

cpp::Point& cpp::Line::Location()
{
	return MyPoint();	
}
	
void cpp::Line::Move(int a_x, int a_y)
{
	MyPoint().X() += a_x;
	MyPoint().Y() += a_y;	
}

double& cpp::Line::Edge()
{
	return m_edge;
}

const double& cpp::Line::Edge() const
{
	return m_edge;
}

cpp::Point& cpp::Line::MyPoint()
{
	return m_point;
}

const cpp::Point& cpp::Line::MyPoint() const
{
	return m_point;
}


