#include "mu_test.h"

#define _USE_MATH_DEFINES
#include <cmath> //M_PI
#include <iostream>
#include <vector>
#include "shape.hpp"
#include "shape_test.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "horizontal_line.hpp"
#include "vertical_line.hpp"


const size_t g_smallSize = 10;

UNIT(simple_circle_area)

	cpp::Circle myCircle(5);
	cpp::Shape *ptrCircle = &myCircle ;
	
	ASSERT_THAT( ptrCircle->Area() - AreaCircle(myCircle.Radius()) < 1);
	
END_UNIT

UNIT(vector_circles_area)

	std::vector<cpp::Shape*> myVector;
	
	Fill(myVector, g_smallSize, MakeSequence(0, g_smallSize));
	
	size_t size = g_smallSize;
	
	while(size-- > 0)
	{
		ASSERT_THAT( myVector[size]->Area() - 314 < 1);
	} 
	
	PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(myVector); 

END_UNIT

UNIT(simple_rectangle_area)

	cpp::Rectangle myRectangle(5,6);
	cpp::Shape *ptrRectangle = &myRectangle ;
	
	ASSERT_EQUAL( ptrRectangle->Area(),AreaRectangle(myRectangle.Height(),myRectangle.Width()));		
	
END_UNIT

UNIT(vector_rectangle_area)

	std::vector<cpp::Shape*> myVector;
	
	FillRect(myVector, g_smallSize, MakeSequence(0, g_smallSize), MakeSequence(0, g_smallSize));
	
	size_t size = g_smallSize;
	
	while(size-- > 0)
	{
		ASSERT_EQUAL( myVector[size]->Area(), 100);
	} 
	
	PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(myVector); 

END_UNIT


UNIT(vector_rectangle_circle)

	std::vector<cpp::Shape*> myVector;
	
	FillRect(myVector, g_smallSize, MakeSequence(0, g_smallSize), MakeSequence(0, g_smallSize));
	
	Fill(myVector, g_smallSize, MakeSequence(0, g_smallSize));
	
	size_t size = g_smallSize*2;
	
	while(size-- > g_smallSize)
	{
		ASSERT_THAT( myVector[size]->Area() - 314 < 1);	
	} 
	
	while(size-- > 0)
	{
		ASSERT_EQUAL( myVector[size]->Area(), 100);	
	} 	
	
	PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(myVector); 

END_UNIT


UNIT(vector_rectangle_circle_new)

    cpp::Shape* a[] = { new cpp::Circle(7), new cpp::Square(4), new cpp::Rectangle(12, 9)};

    double s[] = { 7*M_PI*7, 4*4, 12*9};

    std::vector<cpp::Shape*> v(a, a + sizeof(a)/sizeof(a[0]) );

    for (size_t i = 0; i < v.size(); i++)

    {
        ASSERT_THAT(v[i]->Area() -  s[i] < 1);
    }

    PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(v);

END_UNIT

UNIT(vector_all_shapes_area)

    cpp::Shape* a[] = { new cpp::Circle(7), new cpp::Square(4), new cpp::Rectangle(12, 9), new cpp::VerticalLine(5), new cpp::HorizontalLine(5)};

    double s[] = { 7*M_PI*7, 4*4, 12*9, 0, 0};

    std::vector<cpp::Shape*> v(a, a + sizeof(a)/sizeof(a[0]) );

    for (size_t i = 0; i < v.size(); i++)

    {
        ASSERT_THAT(v[i]->Area() -  s[i] < 1);
    }

    PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(v);

END_UNIT


UNIT(vector_all_shapes_Parimeter)

    cpp::Shape* a[] = { new cpp::Circle(7), new cpp::Square(4), new cpp::Rectangle(12, 9), new cpp::VerticalLine(5), new cpp::HorizontalLine(5)};

    double s[] = { 7*M_PI*2, 4*4, 42, 5, 5};

    std::vector<cpp::Shape*> v(a, a + sizeof(a)/sizeof(a[0]) );

    for (size_t i = 0; i < v.size(); i++)

    {
        ASSERT_THAT(v[i]->Parimeter() -  s[i] < 1);
    }

    PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(v);

END_UNIT


UNIT(vector_all_shapes_Location)

    cpp::Shape* a[] = { new cpp::Circle(7), new cpp::Square(4), new cpp::Rectangle(12, 9), new cpp::VerticalLine(5), new cpp::HorizontalLine(5)};
    cpp::Point p(1,1);

    std::vector<cpp::Shape*> v(a, a + sizeof(a)/sizeof(a[0]) );

    for (size_t i = 0; i < v.size(); i++)
    {
		v[i]->Location(p);
    }
    
    for (size_t i = 0; i < v.size(); i++)
    {
		ASSERT_EQUAL(v[i]->Location().X(), 1);
		ASSERT_EQUAL(v[i]->Location().Y(), 1);		
    }    

    PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(v);

END_UNIT


UNIT(vector_all_shapes_Location2)

    cpp::Shape* a[] = { new cpp::Circle(7), new cpp::Square(4), new cpp::Rectangle(12, 9), new cpp::VerticalLine(5), new cpp::HorizontalLine(5)};
    cpp::Point p(1,1);

    std::vector<cpp::Shape*> v(a, a + sizeof(a)/sizeof(a[0]) );

    for (size_t i = 0; i < v.size(); i++)
    {
		v[i]->Location() = p;
    }
    
    for (size_t i = 0; i < v.size(); i++)
    {
		ASSERT_EQUAL(v[i]->Location().X(), 1);
		ASSERT_EQUAL(v[i]->Location().Y(), 1);		
    }    

    PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(v);

END_UNIT


UNIT(vector_all_shapes_Move)

    cpp::Shape* a[] = { new cpp::Circle(7), new cpp::Square(4), new cpp::Rectangle(12, 9), new cpp::VerticalLine(5), new cpp::HorizontalLine(5)};
    cpp::Point p(1,1);

    std::vector<cpp::Shape*> v(a, a + sizeof(a)/sizeof(a[0]) );

    for (size_t i = 0; i < v.size(); i++)
    {
		v[i]->Location() = p;
    }
    
    for (size_t i = 0; i < v.size(); i++)
    {
		v[i]->Move(5,5);
    }    
    
    for (size_t i = 0; i < v.size(); i++)
    {
		ASSERT_EQUAL(v[i]->Location().X(), 6);
		ASSERT_EQUAL(v[i]->Location().Y(), 6);		
    }    

    PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(v);

END_UNIT


UNIT(vector_all_shapes_draw)

    cpp::Shape* a[] = { new cpp::Circle(7), new cpp::Square(4), new cpp::Rectangle(12, 9), new cpp::VerticalLine(5), new cpp::HorizontalLine(5)};
    cpp::Point p(1,1);

    std::vector<cpp::Shape*> v(a, a + sizeof(a)/sizeof(a[0]) );

    for (size_t i = 0; i < v.size(); i++)
    {
		v[i]->Location() = p;
    }
    
    for (size_t i = 0; i < v.size(); i++)
    {
		v[i]->Move(5,5);
    }    
    
    for (size_t i = 0; i < v.size(); i++)
    {
		v[i]->Draw();	
    }    

    PopContainer<std::vector<cpp::Shape*>, std::vector<cpp::Shape*>::iterator>(v);
    
    ASSERT_PASS();

END_UNIT


TEST_SUITE(test the shape on fire)

	TEST(simple_circle_area)
	TEST(vector_circles_area)
	TEST(simple_rectangle_area)
	TEST(vector_rectangle_area)
	TEST(vector_rectangle_circle)
	TEST(vector_rectangle_circle_new)
	TEST(vector_all_shapes_area)
	TEST(vector_all_shapes_Parimeter)
	TEST(vector_all_shapes_Location)
	TEST(vector_all_shapes_Location2)
	TEST(vector_all_shapes_Move)
	TEST(vector_all_shapes_draw)
	
END_SUITE
