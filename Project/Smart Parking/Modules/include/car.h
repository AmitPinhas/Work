#ifndef __CAR_H__
#define __CAR_H__

typedef struct Car Car ;

Car* CarCreate( int _id , int _timeEnter );

int CarGetId( Car *_car );

int CarGetTime( Car *_car );

#endif /* __CAR_H__ */
