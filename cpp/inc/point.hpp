#ifndef POINT_HPP
#define POINT_HPP

namespace cpp
{
class Point
{
public:
	Point(int a_x = 0, int a_y = 0);
	
	// Point(const Point & a_other) = default
	// ~Point() = default
	// Point& operator=(const Point & a_other) = default	
	
	int& X();
	int& Y();
	const int& X() const;
	const int& Y() const;
	
private:
	int m_x;
	int m_y;
};
}
#endif // POINT_HPP
