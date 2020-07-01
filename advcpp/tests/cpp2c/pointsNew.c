#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h> // strcpy

#define PHASE (2)
#define CURVATURE 1

/***** Phase 1 *****{{ */
#if PHASE >= 1

#define ERROR -1

typedef struct
{
	double m_x;
	double m_y;	

} __Point2D ;

typedef struct
{
	__Point2D m_point;
	char *m_name;	

} __NamedPoint2D ;

void __Point2D_ctor_zero(__Point2D* a_this);

void __Point2D_ctor_two(__Point2D* a_this, double a_x, double a_y);

void __Point2D_copy_ctor(__Point2D* a_this, const __Point2D* a_second);

void __Point2D_copy_ctor_name_point(__Point2D* a_this, const __NamedPoint2D* a_second);

double __Point2D_distance(const __Point2D* a_this, const __Point2D* a_second);

double __Point2D_x(const __Point2D* a_this);

double __Point2D_y(const __Point2D* a_this);

__Point2D* __Point2D_add_point(__Point2D* a_this, const __Point2D* a_second);

__Point2D* __Point2D_mul_factor(__Point2D* a_this, double a_factor);

void Pointless();

void Pointless()
{
	__Point2D p0; 
	__Point2D p1; 
    __Point2D dxy; 

    __Point2D_ctor_zero(&p0);
    __Point2D_ctor_two(&p1, 0, 10);
    __Point2D_ctor_two(&dxy, 4, -7);

    printf("distance p0 --> p1 == %f\n", __Point2D_distance(&p0, &p1));

    __Point2D_add_point(&p1, &dxy);
	printf("%f, %f\n", __Point2D_x(&p1), __Point2D_y(&p1));
	printf("now distance p0 --> p1 == %f\n", __Point2D_distance(&p0, &p1));

}

void __Point2D_ctor_zero(__Point2D* a_this)
{
    a_this->m_x = 0;
    a_this->m_y = 0;     
}

void __Point2D_ctor_two(__Point2D* a_this, double a_x, double a_y)
{
    a_this->m_x = a_x;
    a_this->m_y = a_y;    
}

double __Point2D_distance(const __Point2D* a_this, const __Point2D* a_second)
{
    if(NULL == a_second)
    {
        return ERROR;
    }

	double dx = a_this->m_x - a_second->m_x;
	double dy = a_this->m_y - a_second->m_y;
	return sqrt(dx * dx + dy * dy);    
}

double __Point2D_x(const __Point2D* a_this)
{
    return a_this->m_x;
}

double __Point2D_y(const __Point2D* a_this)
{
    return a_this->m_y;    
}

__Point2D* __Point2D_add_point(__Point2D* a_this, const __Point2D* a_second)
{
    a_this->m_x += a_second->m_x;
    a_this->m_y += a_second->m_y;    

    return a_this;
}

__Point2D* __Point2D_mul_factor(__Point2D* a_this, double a_factor)
{
    a_this->m_x *= a_factor;
    a_this->m_y *= a_factor;    

    return a_this;
}

void __Point2D_copy_ctor(__Point2D* a_this, const __Point2D* a_second)
{
    a_this->m_x = a_second->m_x;
    a_this->m_y = a_second->m_y;    
}


#endif

/* }} ***** Phase 1 *****/

/*----------------------------------------------------------------*/
/***** Phase 2 *****{{ */
#if PHASE >= 2


void __NamedPoint2D_ctor_default(__NamedPoint2D *a_this)
{
    __Point2D_ctor_zero(&a_this->m_point);
    a_this->m_name = (char*) malloc(7);
    strcpy(a_this->m_name, "origin");
}

void __Point2D_copy_ctor_name_point(__Point2D* a_this, const __NamedPoint2D* a_second)
{
    __Point2D_copy_ctor(a_this, &a_second->m_point);
}
void __NamedPoint2D_ctor_two_default(__NamedPoint2D *a_this, double a_x, double a_y)
{
    __Point2D_ctor_two(&a_this->m_point, a_x, a_y);
    a_this->m_name = (char*) malloc(16);    
    strcpy(a_this->m_name, "anonymous Point");    
}

void __NamedPoint2D_ctor_three(__NamedPoint2D *a_this, double a_x, double a_y, const char* a_name)
{
    __Point2D_ctor_two(&a_this->m_point, a_x, a_y);
    a_this->m_name = (char*) malloc(strlen(a_name) + 1);    
    strcpy(a_this->m_name, a_name);    
}

void __NamedPoint2D_ctor_one_default(__NamedPoint2D *a_this, const __Point2D* a_point)
{
    __Point2D_copy_ctor(&a_this->m_point, a_point);
    a_this->m_name = (char*) malloc(16);    
    strcpy(a_this->m_name, "anonymous Point");      
}

void __NamedPoint2D_ctor_two(__NamedPoint2D *a_this, const __Point2D* a_point, const char *a_name)
{
    __Point2D_copy_ctor(&a_this->m_point, a_point);
    a_this->m_name = (char*) malloc(strlen(a_name) + 1);    
    strcpy(a_this->m_name, a_name);      
}

const char *__NamedPoint2D_get_name(const __NamedPoint2D *a_this)
{
    return a_this->m_name;
}

__NamedPoint2D* __NamedPoint2D_mul_factor(__NamedPoint2D* a_this, double a_factor)
{
    __Point2D_mul_factor(&a_this->m_point, a_factor);
    return a_this;
}

double __NamedPoint2D_distance(const __NamedPoint2D* a_this, const __NamedPoint2D* a_second)
{
    return __Point2D_distance(&a_this->m_point, &a_second->m_point);
}

double __NamedPoint2D_distance_point(const __NamedPoint2D* a_this, const __Point2D* a_second)
{
    return __Point2D_distance(&a_this->m_point, a_second);
}

void __NamedPoint2D_destructor(__NamedPoint2D* a_this)
{
    free(a_this->m_name);
}

void dog()
{
	__NamedPoint2D home;
	__Point2D point;
	__NamedPoint2D dog;

    __NamedPoint2D_ctor_three(&home, 5, 7, "home");
    __Point2D_copy_ctor_name_point(&point, &home);
    __NamedPoint2D_ctor_one_default(&dog, &point);
    
    __NamedPoint2D_mul_factor(&dog, 2);
	printf("Distance from %s to %s is %f\n", __NamedPoint2D_get_name(&home), __NamedPoint2D_get_name(&dog), __NamedPoint2D_distance(&home, &dog));

    __NamedPoint2D_destructor(&home);
    __NamedPoint2D_destructor(&dog);    
}

typedef struct 
{
    __NamedPoint2D m_namedPoint;
    __Point2D m_point;


}__Rectangle ;

void __Rectangle_ctor_two_default(__Rectangle* a_this, const __Point2D* a_first, const __Point2D* a_second)
{
    __NamedPoint2D_ctor_two(&a_this->m_namedPoint, a_first, "anonymous Rectangle");
    __Point2D_copy_ctor(&a_this->m_point, a_second);
}

const char *__Rectangle_get_name(const __Rectangle *a_this)
{
    return __NamedPoint2D_get_name(&a_this->m_namedPoint);
}

double __NamedPoint2D_x(const __NamedPoint2D* a_this)
{
    return __Point2D_x(&a_this->m_point);
}

double __NamedPoint2D_y(const __NamedPoint2D* a_this)
{
    return __Point2D_y(&a_this->m_point);
}

double __Rectangle_calc_area(const __Rectangle *a_this)
{
	__Point2D p1;
	double sideA;
    double sideB;
    __Point2D p2;

    __Point2D_ctor_two(&p1, __NamedPoint2D_x(&a_this->m_namedPoint), __Point2D_y(&a_this->m_point));
    __Point2D_ctor_two(&p2, __Point2D_x(&a_this->m_point), __NamedPoint2D_y(&a_this->m_namedPoint));
    sideA = __NamedPoint2D_distance_point(&a_this->m_namedPoint, &p1);
    sideB = __NamedPoint2D_distance_point(&a_this->m_namedPoint, &p2);
	return sideA * sideB * CURVATURE;
}

void area()
{
	__Point2D p0;
	__Point2D p1;
	__Rectangle r;

    __Point2D_ctor_zero(&p0);
    __Point2D_ctor_two(&p1, 12, 12);
    __Rectangle_ctor_two_default(&r, &p0, &p1);
	
	printf("The area of %s is %f\n", __Rectangle_get_name(&r), __Rectangle_calc_area(&r));
	printf("rectangle size %zu", sizeof(r));
}

#endif
/* }} ***** Phase 2 *****/

/*----------------------------------------------------------------*/

int main()
{
#if PHASE >= 1
	Pointless();
#endif

#if PHASE >= 2
	dog();
	area();
#endif

    return 0;
}