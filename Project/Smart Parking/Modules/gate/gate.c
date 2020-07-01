#include <stdlib.h>
#include "gate.h"

#define OPEN 1
#define CLOSED 0

struct Gate{
	int m_id;
	int m_openOrclosed;
};

/* =========================================================== */
/* =========================== API =========================== */
/* =========================================================== */

/* ------------ Gate Create -------------- */
Gate* GateCreate(int _id)
{
	Gate *gate;
	
	gate = (Gate*)malloc(sizeof(Gate));
	if ( NULL == gate )
	{
		return NULL ;
	}
	
	gate -> m_id = _id ;
	gate -> m_openOrclosed = CLOSED ;
	
	return gate ;
}

/* ------------ Gate Open -------------- */
void GateOpen(Gate *_gate)
{
	_gate -> m_openOrclosed = OPEN ;
	return;
}

/* --------- Gate Closed -------------- */
void GateClosed(Gate *_gate)
{
	_gate -> m_openOrclosed = CLOSED ;
	return;	
}

/* ------- Gate Get Status ------------ */
int GateGetStatus(Gate *_gate)
{
	return _gate -> m_openOrclosed;
}

/* -------- Gate Destroy -------------- */
void GateDestroy(Gate *_gate)
{
	free(_gate);
	return;
}

/* -------- Gate Get Size ------------- */
int GateGetSize()
{
	return sizeof(Gate);
}




