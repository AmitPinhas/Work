#include <stdlib.h> /* allocation */
#include <unistd.h> /* sleep */
#include "camera.h"
#include "event.h"

#define FOREVER 1

struct Camera{
	int m_id;
	Queue *m_evnts;
	sem_t m_empty;
	sem_t m_full;
	pthread_t m_thread;
	pthread_mutex_t m_lock;	
};

Event* CameraEventCreate(int _id);	

/* =========================================================== */
/* =========================== API =========================== */
/* =========================================================== */

/* ---------------------- Camera Create ---------------------- */
Camera* CameraCreate( int id , Queue *_queue , pthread_t _thread , sem_t *_empty , sem_t *_full , pthread_mutex_t *_lock )
{
	Camera *camera;
	
	camera = (Camera*)malloc(sizeof(Camera));
	if ( NULL == camera )
	{
		return NULL ;
	}
	
	camera -> m_id = id ;
	camera -> m_evnts = _queue ;
	camera -> m_empty = *_empty ;
	camera -> m_full = *_full ;
	camera -> m_thread = _thread ;
	camera -> m_lock = *_lock ;
	
	return camera ;
}

/* ---------------------- Camera Run ------------------------ */
void* CameraRun(void* _camera)
{
	Event *event;
	
	while(FOREVER)
	{
		event = CameraEventCreate(((Camera*)_camera)->m_id);	
	
		sem_wait(&((Camera*)_camera)->m_full);
		pthread_mutex_lock(&((Camera*)_camera)->m_lock);
	
		QueueInsert( (((Camera*)_camera)->m_evnts) , event );
	
		pthread_mutex_unlock(&((Camera*)_camera)->m_lock);
	
		sem_post(&((Camera*)_camera)->m_empty);	
	}
	
	return NULL;
}


/* -------------------- Camera Destroy --------------------------- */
void CameraDestroy(Camera *_camera)
{
	free(_camera);
	return;
}



int CameraGetSize()
{
	return sizeof(Camera);
}

/* ================================================================== */
/* =========================== local func =========================== */
/* ================================================================== */

/* ---------------------- Camera Event Create ----------------------- */
Event* CameraEventCreate(int _id)
{
	sleep(rand()%5);
	
	return EventCreate(_id);
}	


