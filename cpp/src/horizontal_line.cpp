#include <iostream>
#include "horizontal_line.hpp"

cpp::HorizontalLine::HorizontalLine(double a_edge)
: Line(a_edge)
{
}

void cpp::HorizontalLine::Draw() const
{
	std::cout << "horizontal line: " << Edge() << " point x: " << MyPoint().X() << " point y: " << MyPoint().Y() << '\n' ;	
}
