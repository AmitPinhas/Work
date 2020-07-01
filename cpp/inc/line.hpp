#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"
#include "point.hpp"

namespace cpp
{

class Line : public Shape
{
public:
	Line(double a_edge);
	
	virtual double Area() const;
	virtual double Parimeter() const;
	virtual void Scale(double a_scale);
	
	virtual void Location(cpp::Point const& a_point);
	virtual Point const& Location() const;
	virtual Point& Location();
	
	virtual void Draw() const = 0;
	virtual void Move(int a_x, int a_y);
	
	virtual double& Edge() ;
	virtual const double& Edge() const;
	
	virtual Point& MyPoint();
	virtual const Point& MyPoint() const;	
	
private:	
	double m_edge;
	Point m_point;		
};

}


#endif // LINE_HPP
