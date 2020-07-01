#ifndef __DAILY_H__
#define __DAILY_H__

#define MAX_TIME 23.99
#define MIN_TIME 00.00

enum DailyError {OK , MEETING_ERROR , ERROR_PARAMS , ERROR_OVERFLOW , REALLOC_FAILED } ;

typedef enum DailyError DailyError ;

typedef struct calendar_t calendar_t ;
typedef struct meeting_t meeting_t ;

/*
    Description: Creates a dairy .
    Input: size of the array and inc array block.
    Output: pointer to a new array / pointer NULL .
    ERROR:  NULL - return null pointer , if size<0 or inc<0 or size and inc = 0 , 
                   or dinamic allocation failed .
*/
calendar_t* AD_Creat(int _size , int _blockSize);

/*
    Description: Makes meeting.
    Input: start time , end time and number room.
    Output: pointer to the new meeting .
    ERROR:  NULL - return null pointer , if start_time > end_time or start_time=end_time or start<min time or end>max time , 
                   or dinamic allocation failed .
*/
meeting_t* Creat_Meeting(float _start , float _end, int _number_room);

/*
    Description: destroy meeting
    Input: pointer meeting.
    Output: no output.
    ERROR : no error.
*/
void MeetingDestroy(meeting_t *_ptrMeeting);

/*
    Description: insert meeting to the array.
    Input: pointer to the calendar , end pointer to meeting.
    Output: OK / ERROR_PARAMS / MEETING_ERROR / ERROR_OVERFLOW / REALLOC_FAILED.
    ERROR: ERROR_PARAMS - is one of the pointers is null ot both.
           MEETING_ERROR - If the meeting conflicts with another meeting.
           ERROR_OVERFLOW - if size = num of elemnt and inc=0.
           REALLOC_FAILED - if realloc failed.
             
*/
DailyError DailyInsert(calendar_t *_calendarPtr, meeting_t *_ptrMeeting);

/*
    Description: free dinamic allocation to the array and free dinamic allocation to the structure.
    Input: pointer from calendar_t type to the structure of params.
    Output: no output.
    ERROR : no error.
*/
void DailyDestroy(calendar_t *_calendarPtr);

/*
    Description: Deletes the meeting by the start time.
    Input: pointer to the array and start time.
    Output: OK / ERROR_NO_ELEMNTS / PTR_ERROR.
    Output details: OK - delete successfully 
                    ERROR_NO_ELEMNTS - no element to delete , num of element <=0 .
                    PTR_ERROR -  if the pointers _calendarPtr . 
*/
DailyError DailyRemove(calendar_t *_calendarPtr, float _start_time);

/*
    Description: find the meeting by the start time.
    Input: pointer to the array and start time.
    Output: TRUE / FALSE.
    Error: FALSE - meeting not found or pointer null.
*/
int Find_Meeting(calendar_t *_calendarPtr,float _start_time); 

/*
    Description: print array.
    Input: pointer to the array.
    Output:no output.
    Error: no error.
*/
void Print_AD(calendar_t *_calendarPtr);

#endif
