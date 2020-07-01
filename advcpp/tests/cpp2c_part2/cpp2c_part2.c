
/* #include <cstdio> */

#include <stdio.h>
#include <stdlib.h> // calloc

typedef void* Vtable;

static int g_numOfShapes;

typedef struct
{
	char m_dummy;

} _Color;

typedef struct
{
	Vtable* m_vTable;

} _Scaleable;

typedef struct 
{
	_Scaleable m_scaleable;	
	int m_id;

} _Shape;

typedef enum {_COLOR_RED, _COLOR_GREEN, _COLOR_DEFAULT}_Color_enum;

typedef enum {_SHAPE_DTOR, _SHAPE_DRAW, _SHAPE_DRAW_COLOR, _SHAPE_SCALE, _SHAPE_AREA}_Shape_vitual_Func;

typedef void (*_dtor)(void*);

typedef void (*_draw)(const void *);

typedef void (*_draw_color)(const void *, _Color_enum);

typedef void (*_scale)(void*, double);

typedef double (*_area)(const void *);

 void _Color_set_color(_Color_enum a_color)
 {
	static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
	puts(pallete[a_color]);	 
 }

void _Scaleable_ctor(_Scaleable *a_this, Vtable* a_vtable)
{
	/* MIL */
	a_this->m_vTable = a_vtable;

	/* body */
}

void _Shape_draw(const void *a_this)
{
	printf("Shape::draw() - %d\n", ((_Shape*)a_this)->m_id);	
}

void _Shape_dtor(void *a_this)
{
	_Shape *p = (_Shape*)a_this;
	_Shape_draw(p);
	--g_numOfShapes; 
	printf("Shape::~Shape - %d\n", p->m_id);	

}

void _Shape_draw_color(const void *a_this, _Color_enum a_color)
{
		printf("Shape::draw(c) - %d\n", ((_Shape*)a_this)->m_id);
		_Color_set_color(a_color);
		_Shape_draw(a_this);
		_Color_set_color(_COLOR_DEFAULT);
}

void _Shape_scale(void * , double a_f) 
{ 
	printf("Shape::scale(%f)\n", a_f);
}

double _Shape_area(const void * )
{ 
	return -1; 
}

Vtable _Shape_vtable[5] = {(void*)_Shape_dtor, (void*)_Shape_draw, (void*)_Shape_draw_color ,
                           (void*)_Shape_scale, (void*)_Shape_area};

void _Shape_ctor(_Shape *a_this)
{
	/* MIL */
	_Scaleable_ctor(&a_this->m_scaleable, _Shape_vtable);
	a_this->m_id = ++g_numOfShapes;

	/* body */
	printf("Shape::Shape() - %d\n", a_this->m_id);	
}

void _Shape_copy_ctor(_Shape *a_this, const _Shape *a_rhs)
{
	/* MIL */
	_Scaleable_ctor(&a_this->m_scaleable,  _Shape_vtable);
	a_this->m_id = ++g_numOfShapes;


	/* body */
	printf("Shape::Shape(Shape&) - %d from - %d\n", a_this->m_id, a_rhs->m_id);
}
	

void _Shape_print_inventory() 
{
	printf("Shape::printInventory - %d\n", g_numOfShapes);
}

void _Scaleable_dtor(void * )
{
}

Vtable _Scaleable_vtable[2] = {(void*)_Scaleable_dtor};


void _vtable_dtor(void* a_this)
{
	_Scaleable *p = (_Scaleable*)a_this;
	((_dtor)p->m_vTable[_SHAPE_DTOR])(a_this);

}

void _vtable_draw(const void* a_this)
{
	_Scaleable *p = (_Scaleable*)a_this;
	((_draw)p->m_vTable[_SHAPE_DRAW])(a_this);

}

void _vtable_draw_color(const void* a_this, _Color_enum a_color)
{
	_Scaleable *p = (_Scaleable*)a_this;
	((_draw_color)p->m_vTable[_SHAPE_DRAW_COLOR])(a_this, a_color);

}

void _vtable_scale(void* a_this, double a_f)
{
	_Scaleable *p = (_Scaleable*)a_this;
	((_scale)p->m_vTable[_SHAPE_SCALE])(a_this, a_f);

}

double _vtable_area(const void* a_this)
{
	_Scaleable *p = (_Scaleable*)a_this;
	return ((_area)p->m_vTable[_SHAPE_AREA])(a_this);

}

void _Shape_ctor_vtable(_Shape *a_this, Vtable* a_vtable)
{
	/* MIL */
	_Scaleable_ctor(&a_this->m_scaleable, a_vtable);
	a_this->m_id = ++g_numOfShapes;

	/* body */
	printf("Shape::Shape() - %d\n", a_this->m_id);	
}


typedef struct 
{
	_Shape m_shape;
	double m_radius;

}_Circle;


void _Circle_copy_ctor(_Circle *a_this, const _Circle *a_rhs)
{
	/* MIL */
	_Shape_copy_ctor(&a_this->m_shape, &a_rhs->m_shape);
	a_this->m_radius = a_rhs->m_radius;

	/* body */
	printf("Circle::Circle(Circle&) - %d, r:%f\n", a_this->m_shape.m_id, a_this->m_radius);
}

void _Circle_dtor(void* a_this)
{
	_Shape_dtor(&((_Circle*)a_this)->m_shape);
	printf("Circle::~Circle() - %d, r:%f\n", ((_Circle*)a_this)->m_shape.m_id, ((_Circle*)a_this)->m_radius); 
}

void _Circle_draw(const void* a_this)
{
	printf("Circle::draw()  - %d, r:%f\n", ((_Circle*)a_this)->m_shape.m_id, ((_Circle*)a_this)->m_radius);
}

void _Circle_scale(void * a_this, double a_f)
{
		printf("Circle::scale(%f)\n", a_f);
		((_Circle*)a_this)->m_radius *= a_f;	
}

double _Circle_area(const void* a_this)
{
	return ((_Circle*)a_this)->m_radius * ((_Circle*)a_this)->m_radius * 3.1415;
}

Vtable _Circle_vtable[5] = {(void*)_Circle_dtor, (void*)_Circle_draw, (void*)_Shape_draw_color ,
                           (void*)_Circle_scale, (void*)_Circle_area};

void _Circle_ctor_default(_Circle* a_this)
{
	/* MIL */
	_Shape_ctor_vtable(&a_this->m_shape, _Circle_vtable);
	a_this->m_radius = 1;

	/* body */
	printf("Circle::Circle() - %d, r:%f\n", a_this->m_shape.m_id, a_this->m_radius); 
}

void _Circle_ctor_double(_Circle* a_this, double a_radius)
{
	/* MIL */
	_Shape_ctor_vtable(&a_this->m_shape, _Circle_vtable);
	a_this->m_radius = a_radius;

	/* body */
	printf("Circle::Circle(double) - %d, r:%f\n", a_this->m_shape.m_id, a_this->m_radius); 
}

double _Circle_radius(const _Circle* a_this)
{
	printf("Circle::draw()  - %d, r:%f\n", a_this->m_shape.m_id, a_this->m_radius);
	return a_this->m_radius;
}



void report(const _Shape* a_s) {
	puts("-----report-----");
	_vtable_draw(a_s);
	_Shape_print_inventory();
	puts("-----report-----");
}


void draw(_Shape* obj) { 
	puts("-----draw(Shape&)-----");
	_vtable_scale(obj, 1);
	_vtable_draw(obj);
	
	static _Circle unit;
	_Circle_ctor_double(&unit, 4);
	
	puts("-----draw(Shape&)-----");
}


void draw_circle(_Circle* c) { 
	puts("-----draw(Circle)-----");

    if(_vtable_area(c) > 3.14){
	    static _Circle unit;
		_Circle_ctor_double(&unit, 1);
		_vtable_draw(c);
	    _vtable_scale(c, 3);
    }
    
	_vtable_draw(c);
	puts("-----draw(Circle)-----");
}

void doObjArray(){
	_Circle c1;
	_Circle c2;
	_Circle copy;
	_Shape objects[2];

	_Circle_ctor_default(&c1);
	_Circle_ctor_double(&c2, 9);

	_Circle_copy_ctor((_Circle*)&objects[0], &c1);
	_Circle_copy_ctor((_Circle*)&objects[1], &c2);

    for(int i = 0; i < 3; ++i) 
	{
		_Circle_copy_ctor(&copy, (_Circle*)&objects[i]);
		draw_circle(&copy);
		_vtable_dtor(&copy);
	}	

	_vtable_dtor(&c2);
	_vtable_dtor(&c1);
}



void disappear() 
{
	puts("-----disappear-----");

	_Circle defaultCircle();

	puts("-----disappear-----");
}


double _Circle_diffWhenDoubled(_Circle* a_circle)
{
	double a0 = _vtable_area(a_circle);
	double a1;

	_vtable_scale(a_circle, 2);

	a1 = _vtable_area(a_circle);
	return a1 - a0;
}


double _Shape_diffWhenDoubled(_Shape* a_shape)
{
	double a0 = _vtable_area(a_shape);
	double a1;

	_vtable_scale(a_shape, 2);

	a1 = _vtable_area(a_shape);
	return a1 - a0;
}
/*
void doPointerArray(){
	std::puts("-----doPointerArray-----");
	Shape *array[] =  {
	    new Circle(),
	    new Circle(4)
	};

    for(int i = 0; i < 3; ++i){ 
		array[i]->scale();
		array[i]->draw();
	}

	std::printf("area: %f\n", diffWhenDoubled(*array[2]));

    for(int i = 0; i < 3; ++i) { 
		delete array[i]; 
		array[i] = 0; 
	}

	std::puts("-----doPointerArray-----");
}

class Empty {
public:
    Empty(int id = 0) { std::printf("Empty::Empty(%d)\n", id); }
   ~Empty() { std::puts("Empty::~Empty()");}	
};

class EmptyEmpty  : public Empty{
	int m_i;

public:
	EmptyEmpty(int id) : m_i(id){
		 std::printf("EmptyEmpty::EmptyEmpty(%d)\n", m_i); 
	}
};

class EmptyBag {
	Empty e1;
	Empty e2;
	EmptyEmpty ee;
public: 
	EmptyBag() : e2(2), e1(1), ee(2) {
		std::puts("EmptyBag::EmptyBag()");
	}
	~EmptyBag(){
		std::puts("EmptyBag::~EmptyBag");
	}	
};
 */
int main(/*int argc, char **argv, char **envp*/)
{	

 	printf("---------------Start----------------\n");
    _Circle c;
	_Circle copyC;

	_Circle_ctor_default(&c);
	_Circle_ctor_default(&copyC);
	_Circle_copy_ctor(&c, &copyC);

	printf("0.-------------------------------\n");		
	draw_circle(&copyC);

	printf("+..............\n");		
	draw_circle(&copyC);

	printf("+..............\n");		
	report((_Shape*)&c);

	_vtable_dtor(&copyC);

	printf("1.-------------------------------\n");	
/*	
    doPointerArray();

	std::printf("2.-------------------------------\n");

    doObjArray();

	std::printf("3.-------------------------------\n");

    Shape::printInventory();
    Circle c2 = c;
    c2.printInventory();

	std::printf("4.-------------------------------\n");
   
    Circle olympics[5];
	std::printf("olympic diff %f\n", diffWhenDoubled(olympics[1]));

	std::printf("5.-------------------------------\n");

	std::printf("6.-------------------------------\n");
	EmptyBag eb;
	std::printf("Empty things are: %zu %zu %zu", sizeof(Empty), sizeof(EmptyEmpty), sizeof(EmptyBag) );
	
	std::printf("7.-------------------------------\n");
	disappear();	

	std::printf("---------------END----------------\n"); */

    return 0;
}

