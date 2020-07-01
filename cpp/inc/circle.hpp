#ifndef CIRCLE_HPP
#define CIRCLE_HPP

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

class Circle : public Shape
{
public:
	Circle(double a_radius);	
	
	// Circle(const Circle & a_other) = default
	// ~Circle() = default
	// Circle& operator=(const Circle & a_other) = default
	
	virtual double Area() const;
	virtual double Parimeter() const;
	virtual void Scale(double a_scale);
	
	virtual void Location(Point const& a_point);
	virtual Point const& Location() const;
	virtual Point& Location();
	
	virtual void Draw() const;
	virtual void Move(int a_x, int a_y);
	
	double& Radius() ;
	const double& Radius() const;
	
	Point& MyPoint();
	const Point& MyPoint() const;
		
private:
	double m_radius;
	Point m_point;
};

}

#endif // CIRCLE_HPP
