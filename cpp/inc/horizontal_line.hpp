#ifndef HORIZONTAL_LINE_HPP
#define HORIZONTAL_LINE_HPP

#include "line.hpp"

namespace cpp
{

class HorizontalLine : public Line
{
public:
	HorizontalLine(double a_edge);
	
	// HorizontalLine(const HorizontalLine & a_other) = default
	// ~HorizontalLine() = default
	// HorizontalLine& operator=(const HorizontalLine & a_other) = default	
	
	virtual void Draw() const;		
};

}

#endif // HORIZONTAL_LINE_HPP
