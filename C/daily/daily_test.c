#include <stdio.h>
#include <stdlib.h>
#include "daily.h"
#include "daily_test.h"

#define MAGIC_NUMBER 28011993

void PositiveAdCreat1();
void PositiveAdCreat2();
void PositiveAdCreat3();
void AdCreatSizeNeg();
void AdCreatBlockNeg();
void AdCreatAllNeg();
void AdCreatAllZero();
void AdCreatMallocFailed();
void PositiveMeetingCreat1();
void CreatMeetingStartbigThenEnd();
void CreatMeetingStartEqualEnd();
void CreatMeetingStartSmall();
void CreatMeetingEndBig();
void MeetingDestroyNull();
void MeetingDestroyDoubleFree();
void PositiveDailyInsert();
void DailyInsertNull1();
void DailyInsertNull2();
void DailyInsertNull3();
void DailyInsertMeetingError1();
void DailyInsertMeetingError2();
void DailyInsertMeetingError3();
void DailyInsertMeetingError4();
void DailyInsertMeetingError5();
void DailyInsertMeetingError6();
void DailyInsertMeetingError7();
void DailyInsertOverFlow();
void DailyDestroyNull();
void DailyDestroyDoubleFree();
void PositiveDailyRemove();

char pass[]="pass";
char failed[]="failed";

int main()
{
     PositiveAdCreat1();
     PositiveAdCreat2();
     PositiveAdCreat3();
     AdCreatSizeNeg();
     AdCreatBlockNeg();
     AdCreatAllNeg();
     AdCreatAllZero();
     AdCreatMallocFailed();
     PositiveMeetingCreat1();
     CreatMeetingStartbigThenEnd();
     CreatMeetingStartEqualEnd();
     CreatMeetingStartSmall();
     CreatMeetingEndBig();
     MeetingDestroyNull();
     MeetingDestroyDoubleFree();
     PositiveDailyInsert();
     DailyInsertNull1();
     DailyInsertNull2();
     DailyInsertNull3();
     DailyInsertMeetingError1();
     DailyInsertMeetingError2();
     DailyInsertMeetingError3();
     DailyInsertMeetingError4();
     DailyInsertMeetingError5();
     DailyInsertMeetingError6();
     DailyInsertMeetingError7();
     DailyInsertOverFlow();
     DailyDestroyNull();
     DailyDestroyDoubleFree();
     PositiveDailyRemove();
     
     return OK;
}

void PositiveAdCreat1()
{
     /* size > 0 && block > 0 */
     calendar_t *ptrCalendar;
     int size , block , numElement , magic;
     meeting_t **ptrMeetings;
     
    ptrCalendar = AD_Creat(5 , 6);
    size = GetSize(ptrCalendar);
    block = GetBlock(ptrCalendar);
    numElement = GetNumOfElements(ptrCalendar);
    magic = GetMagic_num(ptrCalendar);
    ptrMeetings = GetArrayMeeting(ptrCalendar);
     
     if ( ptrCalendar != NULL && 5 == size && 6 == block && 0 == numElement && MAGIC_NUMBER == magic && ptrMeetings != NULL )
     {
          puts(pass);
          DailyDestroy(ptrCalendar);
     }
     else
     {
          puts(failed);  
     }
}

void PositiveAdCreat2()
{
     /* size = 0 && block > 0 */
     calendar_t *ptrCalendar;
     int size , block , numElement , magic;
     meeting_t **ptrMeetings;
     
    ptrCalendar = AD_Creat(0 , 6);
    size = GetSize(ptrCalendar);
    block = GetBlock(ptrCalendar);
    numElement = GetNumOfElements(ptrCalendar);
    magic = GetMagic_num(ptrCalendar);
    ptrMeetings = GetArrayMeeting(ptrCalendar);
     
     if ( ptrCalendar != NULL && 0 == size && 6 == block && 0 == numElement && MAGIC_NUMBER == magic && ptrMeetings != NULL )
     {
          puts(pass);
          DailyDestroy(ptrCalendar);
     }
     else
     {
          puts(failed);  
     }
}

void PositiveAdCreat3()
{
     /* size > 0 && block = 0 */
     calendar_t *ptrCalendar;
     int size , block , numElement , magic;
     meeting_t **ptrMeetings;
     
    ptrCalendar = AD_Creat(5 , 0);
    size = GetSize(ptrCalendar);
    block = GetBlock(ptrCalendar);
    numElement = GetNumOfElements(ptrCalendar);
    magic = GetMagic_num(ptrCalendar);
    ptrMeetings = GetArrayMeeting(ptrCalendar);
     
     if ( ptrCalendar != NULL && 5 == size && 0 == block && 0 == numElement && MAGIC_NUMBER == magic && ptrMeetings != NULL )
     {
          puts(pass);
          DailyDestroy(ptrCalendar);
     }
     else
     {
          puts(failed);  
     }
}

void AdCreatSizeNeg()
{
     /* size < 0 && block = 6 */
     calendar_t *ptrCalendar;
     
     ptrCalendar = AD_Creat(-5 , 6);
     
     if ( ptrCalendar == NULL )
     {
          puts(pass);
     }
     else
     {
          puts(failed); 
          DailyDestroy(ptrCalendar); 
     }
}

void AdCreatBlockNeg()
{
     /* size > 0 && block < 0 */
     calendar_t *ptrCalendar;
     
     ptrCalendar = AD_Creat(5 , -6);
     
     if ( ptrCalendar == NULL )
     {
          puts(pass);
     }
     else
     {
          puts(failed); 
          DailyDestroy(ptrCalendar); 
     }
}

void AdCreatAllNeg()
{
     /* size < 0 && block < 0 */
     calendar_t *ptrCalendar;
     
     ptrCalendar = AD_Creat(-5 , -6);
     
     if ( ptrCalendar == NULL )
     {
          puts(pass);
     }
     else
     {
          puts(failed); 
          DailyDestroy(ptrCalendar); 
     }
}

void AdCreatAllZero()
{
     /* size = 0 && block = 0 */
     calendar_t *ptrCalendar;
     
     ptrCalendar = AD_Creat(0 , 0);
     
     if ( ptrCalendar == NULL )
     {
          puts(pass);
     }
     else
     {
          puts(failed); 
          DailyDestroy(ptrCalendar); 
     }
}

void AdCreatMallocFailed()
{
     /* size = -1 && block > 0 */
     calendar_t *ptrCalendar;
     
     ptrCalendar = AD_Creat(-1 , 5);
     
     if ( ptrCalendar == NULL )
     {
          puts(pass);
     }
     else
     {
          puts(failed); 
          DailyDestroy(ptrCalendar); 
     }
}

void PositiveMeetingCreat1()
{
     meeting_t *ptrMeet;
     
     ptrMeet = Creat_Meeting(03.40 , 05.34, 5);
     
     if ( NULL != ptrMeet )
     {
         puts(pass); 
         MeetingDestroy(ptrMeet);
     }
     else
     {
         puts(failed);   
     }
}

void CreatMeetingStartbigThenEnd()
{
     meeting_t *ptrMeet;
     
     ptrMeet = Creat_Meeting(06.40 , 05.34, 5); 
     if ( NULL == ptrMeet )
     {
         puts(pass); 
     }
     else
     {
         puts(failed);   
         MeetingDestroy(ptrMeet);
     }         
}

void CreatMeetingStartEqualEnd()
{
     meeting_t *ptrMeet;
     
     ptrMeet = Creat_Meeting(06.40 , 06.40, 5); 
     if ( NULL == ptrMeet )
     {
         puts(pass); 
     }
     else
     {
         puts(failed);   
         MeetingDestroy(ptrMeet);
     }       
}

void CreatMeetingStartSmall()
{
     meeting_t *ptrMeet;
     
     ptrMeet = Creat_Meeting(-05.06 , 06.40, 5); 
     if ( NULL == ptrMeet )
     {
         puts(pass); 
     }
     else
     {
         puts(failed);   
         MeetingDestroy(ptrMeet);
     }        
}

void CreatMeetingEndBig()
{
     meeting_t *ptrMeet;
     
     ptrMeet = Creat_Meeting(06.40 , 24.45, 5); 
     if ( NULL == ptrMeet )
     {
         puts(pass); 
     }
     else
     {
         puts(failed);   
         MeetingDestroy(ptrMeet);
     }  
}

void MeetingDestroyNull()
{
     MeetingDestroy(NULL);
     puts(pass);
}

void MeetingDestroyDoubleFree()
{
     meeting_t *ptrMeet;
     
     ptrMeet = Creat_Meeting(03.40 , 05.34, 5);
     MeetingDestroy(ptrMeet);
     MeetingDestroy(ptrMeet);
      puts(pass);          
}

void PositiveDailyInsert()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);          
      ptrCalendar = AD_Creat(5 , 6); 
      
      if((result = DailyInsert(ptrCalendar, ptrMeet)) == OK)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      DailyDestroy(ptrCalendar);
}

void DailyInsertNull1()
{
      meeting_t *ptrMeet;     
      DailyError result;
            
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);
      if((result = DailyInsert(NULL, ptrMeet)) == ERROR_PARAMS)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeet);  
}

void DailyInsertNull2()
{
      calendar_t *ptrCalendar;   
      DailyError result;
              
      ptrCalendar = AD_Creat(5 , 6); 
      
      if((result = DailyInsert(ptrCalendar, NULL)) == ERROR_PARAMS)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      DailyDestroy(ptrCalendar);
}

void DailyInsertNull3()
{
      DailyError result;
      if((result = DailyInsert(NULL, NULL)) == ERROR_PARAMS)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }      
}

void DailyInsertMeetingError1()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet , *ptrMeetTwo;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);  
      ptrMeetTwo = Creat_Meeting(03.40 , 05.34, 5);         
      ptrCalendar = AD_Creat(5 , 6); 
      DailyInsert(ptrCalendar, ptrMeet);
      
      if((result = DailyInsert(ptrCalendar, ptrMeetTwo)) == MEETING_ERROR)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeetTwo);  
      DailyDestroy(ptrCalendar);
}

void DailyInsertMeetingError2()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet , *ptrMeetTwo , *ptrMeetThree;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);  
      ptrMeetTwo = Creat_Meeting(06.40 , 07.34, 6);  
      ptrMeetThree = Creat_Meeting(06.40 , 07.34, 6);         
      ptrCalendar = AD_Creat(5 , 6); 
      DailyInsert(ptrCalendar, ptrMeet);
      DailyInsert(ptrCalendar, ptrMeetTwo);
      if((result = DailyInsert(ptrCalendar, ptrMeetThree)) == MEETING_ERROR)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeetThree);  
      DailyDestroy(ptrCalendar);
}

void DailyInsertMeetingError3()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet , *ptrMeetTwo , *ptrMeetThree;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);  
      ptrMeetTwo = Creat_Meeting(06.40 , 07.34, 6);  
      ptrMeetThree = Creat_Meeting(03.40 , 05.34, 6);         
      ptrCalendar = AD_Creat(5 , 6); 
      DailyInsert(ptrCalendar, ptrMeet);
      DailyInsert(ptrCalendar, ptrMeetTwo);
      if((result = DailyInsert(ptrCalendar, ptrMeetThree)) == MEETING_ERROR)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeetThree);  
      DailyDestroy(ptrCalendar);
}

void DailyInsertMeetingError4()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet , *ptrMeetTwo , *ptrMeetThree;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);  
      ptrMeetTwo = Creat_Meeting(06.40 , 07.34, 6);  
      ptrMeetThree = Creat_Meeting(02.40 , 03.41, 6);         
      ptrCalendar = AD_Creat(5 , 6); 
      DailyInsert(ptrCalendar, ptrMeet);
      DailyInsert(ptrCalendar, ptrMeetTwo);
      if((result = DailyInsert(ptrCalendar, ptrMeetThree)) == MEETING_ERROR)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeetThree);  
      DailyDestroy(ptrCalendar);
}

void DailyInsertMeetingError5()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet , *ptrMeetTwo , *ptrMeetThree;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);  
      ptrMeetTwo = Creat_Meeting(06.40 , 07.34, 6);  
      ptrMeetThree = Creat_Meeting(05.33 , 06.30, 6);         
      ptrCalendar = AD_Creat(5 , 6); 
      DailyInsert(ptrCalendar, ptrMeet);
      DailyInsert(ptrCalendar, ptrMeetTwo);
      if((result = DailyInsert(ptrCalendar, ptrMeetThree)) == MEETING_ERROR)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeetThree);  
      DailyDestroy(ptrCalendar);     
}

void DailyInsertMeetingError6()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet , *ptrMeetTwo , *ptrMeetThree;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);  
      ptrMeetTwo = Creat_Meeting(06.40 , 07.34, 6);  
      ptrMeetThree = Creat_Meeting(06.45 , 07.30, 6);         
      ptrCalendar = AD_Creat(5 , 6); 
      DailyInsert(ptrCalendar, ptrMeet);
      DailyInsert(ptrCalendar, ptrMeetTwo);
      if((result = DailyInsert(ptrCalendar, ptrMeetThree)) == MEETING_ERROR)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeetThree);  
      DailyDestroy(ptrCalendar);
}

void DailyInsertMeetingError7()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet , *ptrMeetTwo , *ptrMeetThree;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);  
      ptrMeetTwo = Creat_Meeting(06.40 , 07.34, 6);  
      ptrMeetThree = Creat_Meeting(03.20 , 07.50, 6);         
      ptrCalendar = AD_Creat(5 , 6); 
      DailyInsert(ptrCalendar, ptrMeet);
      DailyInsert(ptrCalendar, ptrMeetTwo);
      if((result = DailyInsert(ptrCalendar, ptrMeetThree)) == MEETING_ERROR)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeetThree);  
      DailyDestroy(ptrCalendar);
}

void DailyInsertOverFlow()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet , *ptrMeetTwo , *ptrMeetThree;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);  
      ptrMeetTwo = Creat_Meeting(06.40 , 07.34, 6);  
      ptrMeetThree = Creat_Meeting(08.20 , 09.50, 6);         
      ptrCalendar = AD_Creat(2 , 0); 
      DailyInsert(ptrCalendar, ptrMeet);
      DailyInsert(ptrCalendar, ptrMeetTwo);
      if((result = DailyInsert(ptrCalendar, ptrMeetThree)) == ERROR_OVERFLOW)
      {
         puts(pass);
      }
      else
      {
         puts(failed);    
      }
      
      MeetingDestroy(ptrMeetThree);  
      DailyDestroy(ptrCalendar);
}

void DailyDestroyNull()
{
     DailyDestroy(NULL);
     puts(pass); 
}

void DailyDestroyDoubleFree()
{
      calendar_t *ptrCalendar;   
      ptrCalendar = AD_Creat(2 , 0);
      DailyDestroy(ptrCalendar);
      DailyDestroy(ptrCalendar);    
      puts(pass);  
}

void PositiveDailyRemove()
{
      calendar_t *ptrCalendar;   
      meeting_t *ptrMeet;
      DailyError result;
     
      ptrMeet = Creat_Meeting(03.40 , 05.34, 5);          
      ptrCalendar = AD_Creat(5 , 6); 
      
      DailyInsert(ptrCalendar, ptrMeet);     
      if((result=DailyRemove(ptrCalendar, 03.40)) == OK )
      {
         puts(pass); 
      }
      else
      {
         puts(failed);  
      }
      DailyDestroy(ptrCalendar);          
}

