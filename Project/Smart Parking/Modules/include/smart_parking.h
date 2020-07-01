#ifndef __SMART_PARKING_H__
#define __SMART_PARKING_H__

typedef struct SmartParking SmartParking;

SmartParking* SmartParkCreate(size_t _capacityParking , size_t _numGateIn );

void SmartParkRun(SmartParking *_smartParking);

#endif /* __SMART_PARKING_H__ */
