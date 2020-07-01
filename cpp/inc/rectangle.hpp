#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>
#include "shape.hpp"
#include "point.hpp"

// is-A
// implements
// inherits
// derives
// sub-type
// concrete

namespace cpp
{

class Rectangle : public Shape
{
public:
	Rectangle(double a_height, double m_width);	
	
	// Rectangle(const Rectangle & a_other) = default
	// ~Rectangle() = default
	// Rectangle& operator=(const Rectangle & a_other) = default
	
	virtual double Area() const;
	virtual double Parimeter() const;
	virtual void Scale(double a_scale);
	
	virtual void Location(Point const& a_point);
	virtual Point const& Location() const;
	virtual Point& Location();
	
	virtual void Draw() const;
	virtual void Move(int a_x, int a_y);	
	
	double& Height();
	double& Width();
	const double& Height() const;
	const double& Width() const;	
	
	Point& MyPoint();
	const Point& MyPoint() const;	
	
private:
	double m_height;
	double m_width;
	Point m_point;	
};

}


#endif // RECTANGLE_HPP
