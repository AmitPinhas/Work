#ifndef __GATE_H__
#define __GATE_H__

typedef struct Gate Gate;

Gate* GateCreate(int _id);

void GateOpen(Gate *_gate);

void GateClosed(Gate *_gate);

int GateGetStatus(Gate *_gate);

void GateDestroy(Gate *_gate);

int GateGetSize();

#endif /* __GATE_H__ */
