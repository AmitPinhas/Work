#ifndef VERTICAL_LINE_HPP
#define VERTICAL_LINE_HPP

#include "line.hpp"

namespace cpp
{

class VerticalLine : public Line
{
public:
	VerticalLine(double a_edge);
	
	// VerticalLine(const VerticalLine & a_other) = default
	// ~VerticalLine() = default
	// VerticalLine& operator=(const VerticalLine & a_other) = default	
	
	virtual void Draw() const;		
};

}

#endif // VERTICAL_LINE_HPP
