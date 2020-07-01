#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <pthread.h>
#include <semaphore.h>

#include "queue.h"

typedef struct Camera Camera;

Camera* CameraCreate( int id , Queue *_queue , pthread_t _thread , sem_t *_empty , sem_t *_full , pthread_mutex_t *_lock);

void* CameraRun(void* _event);

void CameraDestroy(Camera *_camera);

int CameraGetSize();

#endif /* __CAMERA_H__ */
