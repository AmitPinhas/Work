#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"

// super-type
// absract
// interface
// base
// contract

namespace cpp
{
class Shape
{
public:
	// Shape(const Shape & a_other) = delete
	// Shape& operator=(const Shape & a_other) = delete	
	
	virtual ~Shape();
	
	virtual double Area() const = 0;
	virtual double Parimeter() const = 0;
	virtual void Scale(double a_scale) = 0;
	
	virtual void Location(cpp::Point const& a_point) = 0;
	virtual Point const& Location() const = 0;
	virtual Point& Location() = 0;
	
	virtual void Draw() const = 0;
	virtual void Move(int a_x, int a_y) = 0;
};
}

#endif // SHAPE_HPP
