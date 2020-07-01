#ifndef __DAILY_TEST_H__
#define __DAILY_TEST_H__

float GetStartTime(meeting_t *_meet);
float GetEndTime(meeting_t *_meet);
int GetNumberRoom(meeting_t *_meet);
meeting_t** GetArrayMeeting(calendar_t *_calendar);
int GetSize(calendar_t *_calendar);
int GetBlock(calendar_t *_calendar);
int GetNumOfElements(calendar_t *_calendar);
int GetMagic_num(calendar_t *_calendar);

#endif /* __DAILY_TEST_H__ */
