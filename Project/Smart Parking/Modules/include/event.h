#ifndef __EVENT_H__
#define __EVENT_H__

#include "MyMalloc.h"

typedef struct Event Event;

Event* EventCreate(int _idCam);

int EventGetSize();

void EventSetPool(Pool *_pool);

void EventDestroy(Event *_event);

int EventGetIdCam(Event *_event);

int GetIdCar(Event *_event);

#endif /* __EVENT_H__ */
