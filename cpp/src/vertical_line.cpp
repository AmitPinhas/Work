#include <iostream>
#include "vertical_line.hpp"

cpp::VerticalLine::VerticalLine(double a_edge)
: Line(a_edge)
{
}

void cpp::VerticalLine::Draw() const
{
	std::cout << "vertical line: " << Edge() << " point x: " << MyPoint().X() << " point y: " << MyPoint().Y() << '\n' ;	
}
