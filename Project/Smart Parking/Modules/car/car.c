#include <stdlib.h> /* allocation */
#include "car.h"

struct Car{
	int m_id ;
	int m_time;
};

Car* CarCreate( int _id , int _timeEnter )
{
	Car *car ;
	
	car = (Car*)malloc(sizeof(Car));
	if ( NULL == car )
	{
		return NULL;
	}
	
	car->m_id   = _id;
	car->m_time = _timeEnter;
	
	return car;
}

int CarGetId( Car *_car)
{
	return _car -> m_id ;
}

int CarGetTime( Car *_car )
{
	return _car -> m_time ;	
}
