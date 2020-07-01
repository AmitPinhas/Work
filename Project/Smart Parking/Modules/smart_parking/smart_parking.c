#include <stdlib.h> /* allocation */
#include <pthread.h>
#include <unistd.h>  /* sleep */
#include "smart_parking.h"
#include "HashMap.h"
#include "queue.h"
#include "MyMalloc.h"
#include "camera.h"
#include "gate.h"
#include "event.h"
#include "car.h"
#include "time_m.h"

#define FOREVER 1

struct SmartParking{
	HashMap *m_cars;
	Queue *m_queueCameresIn;
	pthread_t *m_cameraInThreads;
	pthread_mutex_t *m_lockCamera;
	pthread_mutex_t *m_lockConsumer;	
	sem_t *m_empty;
	sem_t *m_full;
	Camera **m_cameras;
	Gate **m_gates;
	size_t m_numGate;
};


size_t HashFunctionSmart(const void* _key);
int    EqualityFunctionSmart(const void* _firstKey, const void* _secondKey);
void   SmartOpenGate( SmartParking *_smartParking ,Event *_event );
void   SmartStoreData( SmartParking *_smartParking ,Event *_event );
static void* WaitToEvent(void* _smartParking);
/* =========================================================== */
/* =========================== API =========================== */
/* =========================================================== */

/* --------------------- Smart Park Create ------------------- */
SmartParking* SmartParkCreate(size_t _capacityParking , size_t _numGateIn )
{
	SmartParking *smartPark;
	static int id=1;
	int i=0;
	
	if ( 0 == _capacityParking  || 0 == _numGateIn )
	{
		return NULL ;
	}
	
	smartPark = (SmartParking*)malloc(sizeof(SmartParking));
	if ( NULL == smartPark )
	{
		return NULL ;
	}
	
	smartPark-> m_numGate = _numGateIn;
	
	smartPark->m_cars = HashMapCreate( (_capacityParking/10) , HashFunctionSmart , EqualityFunctionSmart );
	if ( NULL == smartPark->m_cars )
	{
		free(smartPark);
		return NULL;
	}
	
	smartPark -> m_queueCameresIn = QueueCreate( _capacityParking );
	if ( NULL == smartPark -> m_queueCameresIn )
	{
		HashMapDestroy( &(smartPark->m_cars) , NULL , NULL );
		free(smartPark);
		return NULL;
	}
	
	smartPark-> m_cameraInThreads = (pthread_t*)malloc( (_numGateIn*2) * sizeof(pthread_t) );
	
    if ( (pthread_mutex_init( smartPark->m_lockCamera , NULL) != 0) || (pthread_mutex_init( smartPark->m_lockConsumer , NULL) != 0) )
    {
	   HashMapDestroy( &(smartPark->m_cars) , NULL , NULL );
	   free(smartPark-> m_cameraInThreads);
	   free(smartPark);
        return NULL;
    }
	
    sem_init( smartPark->m_empty , 0, 0);	
    sem_init( smartPark->m_full , 0, _capacityParking);
    
    smartPark -> m_cameras = (Camera**)malloc(_numGateIn * sizeof(Camera*) );
    smartPark -> m_gates = (Gate**)malloc(_numGateIn * sizeof(Gate*) );
    
    for ( i = 0 ; i<_numGateIn ; i++ , id++ )
    {
    		smartPark -> m_cameras[i] = CameraCreate( id , smartPark -> m_queueCameresIn , smartPark-> m_cameraInThreads[i] , smartPark->m_empty , smartPark->m_full , smartPark->m_lockCamera );
    		smartPark -> m_gates[i] = GateCreate( id ) ;
    }
    
    EventSetPool ( MyMallocPoolCreate( _capacityParking , EventGetSize() ) ) ;
    
    return smartPark ;	
}

/* ------------------- Smart Park Run ------------------ */
void SmartParkRun(SmartParking *_smartParking)
{
	int i;
	
	for ( i=0 ; i< _smartParking->m_numGate ; i++)
	{
		 pthread_create(&(_smartParking->m_cameraInThreads[i]), NULL , CameraRun , &(_smartParking->m_cameras[i]));
	}
	
	for ( ; i < (_smartParking->m_numGate*2) ; i++ )
	{
		pthread_create(&(_smartParking->m_cameraInThreads[i]), NULL , WaitToEvent , _smartParking );
	}

	for ( i=0 ; i< _smartParking->m_numGate ; i++)
	{
		 pthread_join( _smartParking->m_cameraInThreads[i] , NULL );
	}
	
	return;
}

/* ================================================================== */
/* =========================== local func =========================== */
/* ================================================================== */

/* -------------------- Hash Function ----------------------- */
size_t HashFunctionSmart(const void* _key)
{
	return (size_t)((*(int*)_key) % 100) ; 
}


/* ------------------- Equality Function -------------------- */
int EqualityFunctionSmart(const void* _firstKey, const void* _secondKey)
{
	return  ( *((int*)_firstKey) == *((int*)_secondKey) ) ;
}


/* -------------------- Wait To Event ----------------------- */
static void* WaitToEvent(void* _smartParking)
{
	Event *event;
	
	while(FOREVER)
	{
		sem_wait( ((SmartParking*)_smartParking)->m_empty );
		pthread_mutex_lock( ((SmartParking*)_smartParking)->m_lockConsumer );
	
		QueueRemove(((SmartParking*)_smartParking)->m_queueCameresIn , (void**)&event);
		
		SmartOpenGate( (SmartParking*)_smartParking , event );
		
		SmartStoreData( (SmartParking*)_smartParking , event );
	
		pthread_mutex_unlock( ((SmartParking*)_smartParking)->m_lockConsumer );
	
		sem_post( ((SmartParking*)_smartParking)->m_full );	
	}
	
	return NULL;	
}


/* ----------------------- Smart Open Gate ---------------------- */
void   SmartOpenGate( SmartParking *_smartParking ,Event *_event )
{
	GateOpen( (_smartParking->m_gates[EventGetIdCam(_event)-1]) ) ;
	
	sleep(1);
	
	GateClosed( (_smartParking->m_gates[EventGetIdCam(_event)-1]) ) ;
	
	return;
}

/* ----------------------- Smart Store Data ---------------------- */
void   SmartStoreData( SmartParking *_smartParking ,Event *_event )
{
	Car *car = CarCreate( GetIdCar(_event) , Time_mGetCurrTime() );
	int idCar = CarGetId(car) ;
	
	HashMapInsert( _smartParking->m_cars , &idCar , car ); 
	
	return;
}



