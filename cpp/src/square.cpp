#include <iostream>
#include "square.hpp"

cpp::Square::Square(double a_edge)
: m_edge(a_edge)
{
}

double cpp::Square::Area() const
{
	return Edge() * Edge();
}

double cpp::Square::Parimeter() const
{
	return Edge() * 4;
}

void cpp::Square::Scale(double a_scale)
{
	Edge() *= a_scale;
}

void cpp::Square::Location(cpp::Point const& a_point)
{
	MyPoint().X() = a_point.X();
	MyPoint().Y() = a_point.Y();
}

cpp::Point const& cpp::Square::Location() const
{
	return MyPoint();
}

cpp::Point& cpp::Square::Location()
{
	return MyPoint();	
}

void cpp::Square::Draw() const
{
	std::cout << "edge: " << Edge() << " point x: " << MyPoint().X() << " point y: " << MyPoint().Y() << '\n' ;
}

void cpp::Square::Move(int a_x, int a_y)
{
	MyPoint().X() += a_x;
	MyPoint().Y() += a_y;
}

double& cpp::Square::Edge()
{
	return m_edge;
}

const double& cpp::Square::Edge() const
{
	return m_edge;
}

cpp::Point& cpp::Square::MyPoint()
{
	return m_point;
}

const cpp::Point& cpp::Square::MyPoint() const
{
	return m_point;
}
