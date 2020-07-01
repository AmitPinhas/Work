#include <stdlib.h>
#include "event.h"

Pool *pool;

struct Event{
	int m_idCam;
	int m_idCar;
};


Event* EventCreate(int _idCam)
{
	Event *event;
	static int idCar=0;
	
	event = (Event*)MyMallocAllocateBuffer(pool);	
	event -> m_idCam = _idCam ;	
	event -> m_idCar = ++idCar;
	
	return event;	
}

void EventDestroy(Event *_event)
{
	MyMallocFreeBuffer(pool , _event); 
	return;
}

void EventSetPool(Pool *_pool)
{
	pool = _pool ;
	return;
}

int EventGetSize()
{
	return sizeof(Event);
}

int EventGetIdCam(Event *_event)
{
	return _event -> m_idCam ;
}


int GetIdCar(Event *_event)
{
	return _event -> m_idCar ;
}
