#include <stdio.h>
#include <stdlib.h> /* for allocations */
#include "daily.h"
#include "daily_test.h"

#define MAGIC_NUMBER 28011993
#define MAGIC_NUMBER_MEETING 39911082
#define TRUE 1
#define FALSE 0

DailyError Param_Check_Creat(int _size ,int _blockSize);
DailyError CheckIncrementAlloc(calendar_t *_calendarPtr, meeting_t *_ptrMeeting);
DailyError Sort_By_Start_time(calendar_t *_calendarPtr);
DailyError Go_End(calendar_t *_calendarPtr ,int _index);

struct calendar_t{
     meeting_t **dArray;
     int dArraySize;
     int dArrayBlock;
     int NumOfElements;
     int magic_num;
};

struct meeting_t{
     float start_time;
     float end_time;
     int number_room;
     int magic_num;
};

calendar_t* AD_Creat(int _size , int _blockSize)
{
     calendar_t *ptr_param;
     DailyError result_check;

     if((result_check=Param_Check_Creat(_size , _blockSize)) != OK)
     {
          return NULL;
     }    
     
     ptr_param = (calendar_t*)malloc(sizeof(calendar_t)); 

     if ( NULL == ptr_param)
     {
          return NULL;
     }
     
     ptr_param->dArray = (meeting_t**)malloc((_size) * sizeof(meeting_t*));     
     
     if( NULL == ptr_param->dArray)
     {
          free(ptr_param);
          return NULL;
     }
     
     ptr_param->dArraySize= _size;
     ptr_param->dArrayBlock= _blockSize;
     ptr_param->NumOfElements=0;
     ptr_param->magic_num =MAGIC_NUMBER;
     
     return ptr_param;     
}

meeting_t* Creat_Meeting(float _start , float _end , int _number_room)
{
     meeting_t *ptr_meeting;      
     
     if((_start >= _end) || _start<MIN_TIME || _end>MAX_TIME)
     {
          return NULL;
     }
     
     ptr_meeting=(meeting_t*)malloc(sizeof(meeting_t));
     
     if ( NULL == ptr_meeting  )
     {
          return NULL;
     }
          
     ptr_meeting->start_time=_start;
     ptr_meeting->end_time=_end;
     ptr_meeting->number_room=_number_room;
     ptr_meeting->magic_num=MAGIC_NUMBER_MEETING;
     
     return ptr_meeting;
}

void MeetingDestroy(meeting_t *_ptrMeeting)
{
     if ( _ptrMeeting != NULL && _ptrMeeting->magic_num == MAGIC_NUMBER_MEETING)
     {
        _ptrMeeting->magic_num = 0 ;
        free(_ptrMeeting);
     }
}

DailyError DailyInsert(calendar_t *_calendarPtr, meeting_t *_ptrMeeting)
{
     int index;
     DailyError result_check;     
     
     if(_calendarPtr == NULL || _ptrMeeting == NULL)
     {
          return ERROR_PARAMS;
     }
     
     if(_calendarPtr->NumOfElements==0)
     {  
        _calendarPtr->dArray[_calendarPtr->NumOfElements]=_ptrMeeting;
        _calendarPtr->NumOfElements +=1;    
           return OK;
     }
     
     if(_calendarPtr->NumOfElements==1)
     {
      if(_ptrMeeting->start_time >= _calendarPtr->dArray[0]->end_time || _ptrMeeting->end_time <= _calendarPtr->dArray[0]->start_time)   
      {
        if((result_check = CheckIncrementAlloc(_calendarPtr , _ptrMeeting)) != OK)
        {
             return result_check;
        } 
        else
        {       
        _calendarPtr->dArray[_calendarPtr->NumOfElements]=_ptrMeeting;
        _calendarPtr->NumOfElements +=1;
        Sort_By_Start_time(_calendarPtr);
           return OK;
        }
      }
      else
      {
          return MEETING_ERROR;
      }
     }
     
     if( _calendarPtr->dArray[_calendarPtr->NumOfElements-1]->end_time  <= _ptrMeeting->start_time )
     {
     if((result_check = CheckIncrementAlloc(_calendarPtr , _ptrMeeting)) != OK)
        {
             return result_check;
        }       
     _calendarPtr->dArray[_calendarPtr->NumOfElements]=_ptrMeeting;
     _calendarPtr->NumOfElements +=1;
     Sort_By_Start_time(_calendarPtr);
           return OK;          
     }
     
     if( _calendarPtr->dArray[0]->start_time  >= _ptrMeeting->end_time )
     {
     if((result_check = CheckIncrementAlloc(_calendarPtr , _ptrMeeting)) != OK)
        {
             return result_check;
        }       
     _calendarPtr->dArray[_calendarPtr->NumOfElements]=_ptrMeeting;
     _calendarPtr->NumOfElements +=1;
     Sort_By_Start_time(_calendarPtr);
           return OK;          
     }        
     
     for(index=0 ; index < _calendarPtr->NumOfElements-1 ; index++)
     {
          if(_ptrMeeting->start_time < _calendarPtr->dArray[index]->end_time || _ptrMeeting->end_time > _calendarPtr->dArray[index+1]->start_time)
          {
               return MEETING_ERROR;
          }
     }
     
     if((result_check = CheckIncrementAlloc(_calendarPtr , _ptrMeeting)) != OK)
        {
             return result_check;
        }      
            
     _calendarPtr->dArray[_calendarPtr->NumOfElements]=_ptrMeeting;
     _calendarPtr->NumOfElements +=1;
     
     Sort_By_Start_time(_calendarPtr);
     
     return OK;
}

void DailyDestroy(calendar_t *_calendarPtr)
{
     int index;
     
     if(_calendarPtr != NULL && _calendarPtr->magic_num == MAGIC_NUMBER)
     {          
       _calendarPtr->magic_num =0;   
  
         for(index =0 ; index < _calendarPtr->dArraySize ; index++)
         {
          if(_calendarPtr->dArray[index] != NULL)
          {
          free(_calendarPtr->dArray[index]);
          }
         }
         free(_calendarPtr->dArray);       
       
       free(_calendarPtr);
     }     
}

DailyError DailyRemove(calendar_t *_calendarPtr, float _start_time)
{
     int index;
     meeting_t **ptr;
     
     for(index=0 ; index< _calendarPtr->dArraySize , _start_time <= _calendarPtr->dArray[index]->start_time ; index++)
     {
          if( _calendarPtr->dArray[index]->start_time == _start_time)
          {
               Go_End(_calendarPtr , index);
          }
     }
     
     _calendarPtr->NumOfElements -=1;
     _calendarPtr->dArraySize -=1;
     
          if((ptr=(meeting_t**)realloc(_calendarPtr->dArray , sizeof(meeting_t*)*(_calendarPtr->dArraySize))) == NULL)
          {
               return REALLOC_FAILED;
          }   
          
        _calendarPtr->dArray = ptr; 
     
     return OK;
}

int Find_Meeting(calendar_t *_calendarPtr,float _start_time)
{
     int index;
     
     if ( NULL == _calendarPtr)
     {
          return FALSE ;
     }
     
     for(index=0 ; index< _calendarPtr->NumOfElements , _calendarPtr->dArray[index]->start_time <= _start_time  ; index++)
     {
          if(_start_time == _calendarPtr->dArray[index]->start_time)
          {
               return TRUE;
          }
     }
     
     return FALSE;
}

void Print_AD(calendar_t *_calendarPtr)
{
     int index;
     
     for(index=0 ; index< _calendarPtr->dArraySize ; index++)
     {
      printf("meeting %d : start %f , end %f , number room %d\n" , index+1 , _calendarPtr->dArray[index]->start_time , _calendarPtr->dArray[index]->end_time , _calendarPtr->dArray[index]->number_room);
          
     }     
     
}

DailyError Param_Check_Creat(int _size ,int _blockSize)
{
     if(_size<0 || _blockSize<0)
     {
          return ERROR_PARAMS;
     }
     
     if(_size==0 && _blockSize ==0)
     {
          return ERROR_PARAMS;
     }
     
     return OK;
}

DailyError CheckIncrementAlloc(calendar_t *_calendarPtr, meeting_t *_ptrMeeting)
{
     meeting_t **ptr;     
     
     if(_calendarPtr->NumOfElements == _calendarPtr->dArraySize)
     {
          if (0 == _calendarPtr->dArrayBlock)
          {
               return ERROR_OVERFLOW;
          }    
        
          if((ptr=(meeting_t**)realloc(_calendarPtr->dArray , sizeof(meeting_t*)*((_calendarPtr->dArraySize)+_calendarPtr->dArrayBlock))) == NULL)
          {
               return REALLOC_FAILED;
          } 
          
          _calendarPtr->dArray =  ptr ;   
          _calendarPtr->dArraySize +=_calendarPtr->dArrayBlock;
          _calendarPtr->dArray=ptr;
            
     }

     return OK;
}

DailyError Sort_By_Start_time(calendar_t *_calendarPtr)
{
     int index , index2 , change=1;
     meeting_t *tmp;
     
     while(change)
     {
     for(index = 0 , index2 = index+1 , change=0; index2 < _calendarPtr->NumOfElements ; index++ , index2++)
     {
          if(_calendarPtr->dArray[index]->start_time > _calendarPtr->dArray[index2]->start_time)
          {
               tmp = _calendarPtr->dArray[index];
               _calendarPtr->dArray[index] = _calendarPtr->dArray[index2];
               _calendarPtr->dArray[index2] = tmp;
               change=1;
          }
     }   
     }
     return OK;
}

DailyError Go_End(calendar_t *_calendarPtr ,int _index)
{
     int index2;
     meeting_t *tmp;
     
     for(index2=_index+1 ; index2<_calendarPtr->dArraySize ; index2++)
     {
          tmp = _calendarPtr->dArray[index2-1];
          _calendarPtr->dArray[index2-1] = _calendarPtr->dArray[index2];
          _calendarPtr->dArray[index2] = tmp;
     }
     
     return OK;
}

float GetStartTime(meeting_t *_meet)
{
     return _meet->start_time;
}
float GetEndTime(meeting_t *_meet)
{
     return _meet->end_time;
}
int GetNumberRoom(meeting_t *_meet)
{
     return _meet->number_room;
}

meeting_t** GetArrayMeeting(calendar_t *_calendar)
{
     return _calendar->dArray;
}
int GetSize(calendar_t *_calendar)
{
     return _calendar->dArraySize;
}
int GetBlock(calendar_t *_calendar)
{
     return _calendar->dArrayBlock;
}
int GetNumOfElements(calendar_t *_calendar)
{
     return _calendar->NumOfElements;
}
int GetMagic_num(calendar_t *_calendar)
{
     return _calendar->magic_num;
}
