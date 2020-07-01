#ifndef SQUARE_HPP
#define SQUARE_HPP

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

class Square : public Shape
{
public:
	Square(double a_edge);

	// Square(const Square & a_other) = default
	// ~Square() = default
	// Square& operator=(const Square & a_other) = default
	
	virtual double Area() const;
	virtual double Parimeter() const;
	virtual void Scale(double a_scale);
	
	virtual void Location(Point const& a_point);
	virtual Point const& Location() const;
	virtual Point& Location();
	
	virtual void Draw() const;
	virtual void Move(int a_x, int a_y);
	
	double& Edge() ;
	const double& Edge() const;
	
	Point& MyPoint();
	const Point& MyPoint() const;			
	
private:
	double m_edge;
	Point m_point;	
};

}

#endif // SQUARE_HPP
