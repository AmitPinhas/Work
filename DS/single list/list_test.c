#include <stdio.h>
#include <string.h> /* strcpy */
#include "list.h"

void PositiveInsertHead1();
void PositiveInsertHead2();
void NegativeInsertHead1();
void PositiveRemoveHead1();
void PositiveRemoveHead2();
void NegativeRemoveHead1();
void NegativeRemoveHead2();
void PositiveListInsertByKey1();
void PositiveListInsertByKey2();
void PositiveListInsertByKey3();
void PositiveListInsertByKey4();
void NegativeListInsertByKey1();
void NegativeListInsertByKey2();
void PositiveListInsertByKeyRec1();
void PositiveListInsertByKeyRec2();
void PositiveListInsertByKeyRec3();
void PositiveListInsertByKeyRec4();
void NegativeListInsertByKeyRec1();
void NegativeListInsertByKeyRec2();
void PositiveListRemoveByKey1();
void PositiveListRemoveByKey2();
void NegativeListRemoveByKey1();
void NegativeListRemoveByKey2();
void PositiveListRemoveByKeyRec1();
void PositiveListRemoveByKeyRec2();
void NegativeListRemoveByKeyRec1();
void NegativeListRemoveByKeyRec2();
void PositiveFlip1();
void NegativeFlip1();
void NegativeFlip2();

void DetectLoopNoLoop();
void DetectLoopNull();
void DetectLoopOneItem();
void DetectLoopTrue();
void DetectLoopTrue2();
void DetectLoopTrue3();
void DetectLoopTrueEven();

/* test for func DetectLoop */
void DoLoop(Person *_head);
void DoLoop2(Person *_head);
void DoLoopHead(Person *_head);

char pass[]="PASS";



int main()
{
     PositiveInsertHead1();
     PositiveInsertHead2();
     NegativeInsertHead1();
     PositiveRemoveHead1();
     PositiveRemoveHead2();
     NegativeRemoveHead1();
     NegativeRemoveHead2();
     PositiveListInsertByKey1();
     PositiveListInsertByKey2();
     PositiveListInsertByKey3();
     PositiveListInsertByKey4();
     NegativeListInsertByKey1();
     NegativeListInsertByKey2();
     PositiveListInsertByKeyRec1();
     PositiveListInsertByKeyRec2();
     PositiveListInsertByKeyRec3();
     PositiveListInsertByKeyRec4();
     NegativeListInsertByKeyRec1();
     NegativeListInsertByKeyRec2();
     PositiveListRemoveByKey1();
     PositiveListRemoveByKey2();
     NegativeListRemoveByKey1();
     NegativeListRemoveByKey2();
     PositiveListRemoveByKeyRec1();
     PositiveListRemoveByKeyRec2();
     NegativeListRemoveByKeyRec1();
     NegativeListRemoveByKeyRec2();
     PositiveFlip1();
     NegativeFlip1();
     NegativeFlip2();

	DetectLoopNoLoop();	
     DetectLoopNull();
     DetectLoopOneItem();
     DetectLoopTrue();
     DetectLoopTrue2();
     DetectLoopTrue3();
     DetectLoopTrueEven();
	
     return 1;
}

void PositiveInsertHead1()
{
     /* head null */
     Person p , *head;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;
     
     head = ListInsertHead(NULL ,&p);
     
     if ( head != NULL && (head->m_id == p.m_id))
     {
       puts(pass);
     }
     else
     {
       printf("pos insert head 1 Faild\n");
     }
}

void PositiveInsertHead2()
{
     /* head != null , p != null */
     Person p , *head , p2 , *head2;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;

     p2.m_id = 1234;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14; 
         
     head = ListInsertHead(NULL ,&p);
     head2 = ListInsertHead(head ,&p2);
     
     if ( head2 != NULL && (head2 -> m_id == p2.m_id))
     {
       puts(pass);
     }
     else
     {
       printf("pos insert head 2 Faild\n");
     }
}

void NegativeInsertHead1()
{
     /* _p null */
     Person p , *head , *head2 ;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;
     
     head = ListInsertHead(NULL ,&p);
     
     head2 = ListInsertHead(head ,NULL);
     
     if ( head == head2)
     {
         puts(pass);  
     }
     else
     {
       printf("neg insert head 1 Faild\n");   
     }
}

void PositiveRemoveHead1()
{
     /*from 2 person to 1 */
     Person p , *head , p2 , *head2 , *head3 , *item;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;

     p2.m_id = 1234;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14; 
         
     head = ListInsertHead(NULL ,&p);
     head2 = ListInsertHead(head ,&p2);  
     
     head3 = ListRemoveHead(head2 , &item);  
     
     if(head3->m_id == 123 && item->m_age == 14)
     {
       puts(pass);    
     }
     else
     {
        printf("pos remove head 1 Faild\n");  
     }    
}

void PositiveRemoveHead2()
{
     /*from 1 person to 0 */
     Person p , *head , *head2 , *item;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;
         
     head = ListInsertHead(NULL ,&p);
      
     head2 = ListRemoveHead(head , &item);  
     
     if(head2 == NULL && item->m_age == 12)
     {
       puts(pass);    
     }
     else
     {
        printf("pos remove head 2 Faild\n");  
     } 
}

void NegativeRemoveHead1()
{
     /*head null */
     Person *head  , *item;
      
     head = ListRemoveHead(NULL , &item);  
     
     if(head == NULL )
     {
       puts(pass);    
     }
     else
     {
        printf("neg remove head 1 Faild\n");  
     } 
}

void NegativeRemoveHead2()
{
     /*item null */
     Person p , *head , *head2;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;     
      
     head = ListInsertHead(NULL ,&p); 
     head2 = ListRemoveHead(head , NULL);  
     
     if(head == head2 )
     {
       puts(pass);    
     }
     else
     {
        printf("neg remove head 2 Faild\n");  
     } 
}

void PositiveListInsertByKey1()
{
     /* head is null */
     Person p , *head;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     head = ListInsertByKey(NULL, 123, &p); 
     
     if ( head->m_id == 123)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list insert by key 1 Faild\n");  
     }     
}

void PositiveListInsertByKey2()
{
     /* insert to first */
     Person p , *head , p2 , *head2;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     p2.m_id = 12;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14;      
     
     head = ListInsertByKey(NULL, 123, &p);
     head2 = ListInsertByKey(head, 12, &p2);  
     
     if ( head2->m_id == 12)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list insert by key 2 Faild\n");  
     }   
}

void PositiveListInsertByKey3()
{
     /* insert to second */
     Person p , *head , p2 , *head2;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     p2.m_id = 127;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14;      
     
     head = ListInsertByKey(NULL, 123, &p);
     head2 = ListInsertByKey(head, 127, &p2);  
     if ( head2->m_next->m_id == 127)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list insert by key 3 Faild\n");  
     }  
}

void PositiveListInsertByKey4()
{
     /* insert to third */
     Person p , *head , p2 , *head2 , p3 , *head3;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     p2.m_id = 127;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14;      

     p3.m_id = 1275;
     strcpy(p3.m_name , "ami");
     p3.m_age = 11; 
     
     head = ListInsertByKey(NULL, 123, &p);
     head2 = ListInsertByKey(head, 127, &p2); 
     head3 = ListInsertByKey(head2, 1275, &p3);
     
     if(head3 -> m_next -> m_next -> m_id == 1275)
     {
          puts(pass);
     }
     else
     {
       printf("pos list insert by key 4 Faild\n");   
     } 
}

void NegativeListInsertByKey1()
{
     /* person null*/
     Person p , *head  , *head2  ;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     head = ListInsertByKey(NULL, 123, &p);
     head2 = ListInsertByKey(head, 123, NULL);
     
     if( head2 == head )
     {
          puts(pass);
     }
     else
     {
       printf("neg list insert by key 1 Faild\n");   
     } 
}

void NegativeListInsertByKey2()
{
     /* key already exist*/
     Person p , *head  , *head2 , p2  ;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  

     p2.m_id = 123;
     strcpy(p2.m_name , "amit");
     p2.m_age = 12;
     
     head = ListInsertByKey(NULL, 123, &p);
     head2 = ListInsertByKey(head, 123, &p2);
     
     if( head2 == head && (head2->m_next == NULL))
     {
          puts(pass);
     }
     else
     {
       printf("neg list insert by key 2 Faild\n");   
     } 
}

void PositiveListInsertByKeyRec1()
{
     /* head is null */
     Person p , *head;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     head = ListInsertByKeyRec(NULL, 123, &p); 
     
     if ( head->m_id == 123)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list insert by key rec 1 Faild\n");  
     }     
}
void PositiveListInsertByKeyRec2()
{
     /* insert to first */
     Person p , *head , p2 , *head2;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     p2.m_id = 12;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14;      
     
     head = ListInsertByKeyRec(NULL, 123, &p);
     head2 = ListInsertByKeyRec(head, 12, &p2);  
     
     if ( head2->m_id == 12)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list insert by key rec 2 Faild\n");  
     }
}
void PositiveListInsertByKeyRec3()
{
     /* insert to second */
     Person p , *head , p2 , *head2;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     p2.m_id = 127;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14;      
     
     head = ListInsertByKeyRec(NULL, 123, &p);
     head2 = ListInsertByKeyRec(head, 127, &p2);  
     if ( head2->m_next->m_id == 127)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list insert by key rec 3 Faild\n");  
     } 
}
void PositiveListInsertByKeyRec4()
{
     /* insert to third */
     Person p , *head , p2 , *head2 , p3 , *head3;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     p2.m_id = 127;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14;      

     p3.m_id = 1275;
     strcpy(p3.m_name , "ami");
     p3.m_age = 11; 
     
     head = ListInsertByKeyRec(NULL, 123, &p);
     head2 = ListInsertByKeyRec(head, 127, &p2); 
     head3 = ListInsertByKeyRec(head2, 1275, &p3);
     
     if(head3 -> m_next -> m_next -> m_id == 1275)
     {
          puts(pass);
     }
     else
     {
       printf("pos list insert by key rec 4 Faild\n");   
     } 
}
void NegativeListInsertByKeyRec1()
{
     /* person null*/
     Person p , *head  , *head2  ;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     head = ListInsertByKeyRec(NULL, 123, &p);
     head2 = ListInsertByKeyRec(head, 123, NULL);
     
     if( head2 == head )
     {
          puts(pass);
     }
     else
     {
       printf("neg list insert by key rec 1 Faild\n");   
     } 
}
void NegativeListInsertByKeyRec2()
{
     /* key already exist*/
     Person p , *head  , *head2 , p2  ;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  

     p2.m_id = 123;
     strcpy(p2.m_name , "amit");
     p2.m_age = 12;
     
     head = ListInsertByKeyRec(NULL, 123, &p);
     head2 = ListInsertByKeyRec(head, 123, &p2);
     
     if( head2 == head && (head2->m_next == NULL))
     {
          puts(pass);
     }
     else
     {
       printf("neg list insert by key rec 2 Faild\n");   
     } 
}

void PositiveListRemoveByKey1()
{
     /* 1 person */
     Person p , *head , *head2 , *p1;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     head = ListInsertByKey(NULL, 123, &p); 
     head2 = ListRemoveByKey(head , 123 , &p1);
     
     if ( head2 == NULL && p1->m_id == 123)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list remove by key 1 Faild\n");  
     }
}

void PositiveListRemoveByKey2()
{
     /* 2 person */
     Person p , *head , *head2 , *p1 , p2 , *head3;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  

     p2.m_id = 124;
     strcpy(p2.m_name , "amit");
     p2.m_age = 12;  
          
     head = ListInsertByKey(NULL, 123, &p); 
     head2 = ListInsertByKey(head , 124 , &p2);
     head3 = ListRemoveByKey(head2 , 124, &p1);
       
     if ( head3->m_next == NULL && p1->m_id == 124)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list remove by key 2 Faild\n");  
     }
}

void NegativeListRemoveByKey1()
{
     /* head null */
     Person p , *head , *p1;

     head = ListRemoveByKey(NULL , 123 , &p1);
     
     if ( head == NULL )
     {
       puts(pass);   
     }    
     else
     {
        printf("neg list remove by key 1 Faild\n");  
     }
}

void NegativeListRemoveByKey2()
{
     /* person null */
     Person p , *head , *p1 , *head2;

     p.m_id = 124;
     strcpy(p.m_name , "amit");
     p.m_age = 12;            
     head = ListInsertByKey(NULL, 124, &p);

     head2 = ListRemoveByKey(head , 123 , NULL);
     
     if ( head2 == head )
     {
       puts(pass);   
     }    
     else
     {
        printf("neg list remove by key 2 Faild\n");  
     }
}

void PositiveListRemoveByKeyRec1()
{
     /* 1 person */
     Person p , *head , *head2 , *p1;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  
     
     head = ListInsertByKey(NULL, 123, &p); 
     head2 = ListRemoveByKeyRec(head , 123 , &p1);
     
     if ( head2 == NULL && p1->m_id == 123)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list remove by key rec 1 Faild\n");  
     }
}
void PositiveListRemoveByKeyRec2()
{
     /* 2 person */
     Person p , *head , *head2 , *p1 , p2 , *head3;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;  

     p2.m_id = 124;
     strcpy(p2.m_name , "amit");
     p2.m_age = 12;  
          
     head = ListInsertByKey(NULL, 123, &p); 
     head2 = ListInsertByKey(head , 124 , &p2);
     head3 = ListRemoveByKeyRec(head2 , 124, &p1);
       
     if ( head3->m_next == NULL && p1->m_id == 124)
     {
       puts(pass);   
     }    
     else
     {
        printf("pos list remove by key rec 2 Faild\n");  
     }
}
void NegativeListRemoveByKeyRec1()
{
     /* head null */
     Person p , *head , *p1;

     head = ListRemoveByKeyRec(NULL , 123 , &p1);
     
     if ( head == NULL )
     {
       puts(pass);   
     }    
     else
     {
        printf("neg list remove by key rec 1 Faild\n");  
     }
}
void NegativeListRemoveByKeyRec2()
{
     /* person null */
     Person p , *head , *p1 , *head2;

     p.m_id = 124;
     strcpy(p.m_name , "amit");
     p.m_age = 12;            
     head = ListInsertByKey(NULL, 124, &p);

     head2 = ListRemoveByKey(head , 123 , NULL);
     
     if ( head2 == head )
     {
       puts(pass);   
     }    
     else
     {
        printf("neg list remove by key rec 2 Faild\n");  
     }
}

void PositiveFlip1()
{
     /* 3 person */
     Person p , *head , p2 , *head2 , p3 , *head3 , *head4;
     
     p.m_id = 3;
     strcpy(p.m_name , "amit");
     p.m_age = 15;

     p2.m_id = 2;
     strcpy(p2.m_name , "yarden");
     p2.m_age = 14; 

     p3.m_id = 1;
     strcpy(p3.m_name , "yosi");
     p3.m_age = 13; 
         
     head = ListInsertHead(NULL ,&p);
     head2 = ListInsertHead(head ,&p2);
     head3 = ListInsertHead(head2 ,&p3);
     
     printf("before flip\n");
     PrintList(head3);    
     head4 = Flip(head3);
     printf("after flip\n");
     PrintList(head4);
}

void NegativeFlip1()
{
     /* 1 person */
     Person p , *head  , *head2 ;
     
     p.m_id = 3;
     strcpy(p.m_name , "amit");
     p.m_age = 15;
         
     head = ListInsertHead(NULL ,&p);
          
     printf("before flip\n");
     PrintList(head);    
     head2 = Flip(head);
     printf("after flip\n");
     PrintList(head2);     
}
void NegativeFlip2()
{
     /* pointer null */
     Person *head ;
              
     head = Flip(NULL);
     
     if ( NULL == head)
     {
       puts(pass);   
     }   
     else
     {
       printf("neg flip 2 Faild\n");    
     } 
}

void DetectLoopNoLoop()
{
	int result ;
     Person p , *head , p2 , *head2;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;

     p2.m_id = 1234;
     strcpy(p2.m_name , "amittt");
     p2.m_age = 14; 
         
     head = ListInsertHead(NULL ,&p);
     head2 = ListInsertHead(head ,&p2);
     
     result = DetectLoop(head2);
     if ( result == FALSE )
     {    
       puts(pass);
     }
     else
     {
       printf("Detect Loop No Loop Faild\n");
     }	
}

void DetectLoopNull()
{
	int result ;
	
     result = DetectLoop(NULL);
     
     if ( result == FALSE )
     {    
       puts(pass);
     }
     else
     {
       printf("Detect Loop Null Faild\n");
     }	
}

void DetectLoopOneItem()
{
	int result ;
     Person p , *head ;
     
     p.m_id = 123;
     strcpy(p.m_name , "amit");
     p.m_age = 12;

     head = ListInsertHead(NULL ,&p);
     
     result = DetectLoop(head);
     if ( result == FALSE )
     {    
       puts(pass);
     }
     else
     {
       printf("DetectLoopOneItem Faild\n");
     }	
}

void DetectLoopTrue()
{
     Person p , *head , p2 , *head2 , p3 , *head3 , *head4;
     int result;
     
     p.m_id = 3;
     strcpy(p.m_name , "amit");
     p.m_age = 15;

     p2.m_id = 2;
     strcpy(p2.m_name , "yarden");
     p2.m_age = 14; 

     p3.m_id = 1;
     strcpy(p3.m_name , "yosi");
     p3.m_age = 13; 
         
     head = ListInsertHead(NULL ,&p);
     head2 = ListInsertHead(head ,&p2);
     head3 = ListInsertHead(head2 ,&p3);
     
     DoLoop(head3);
     result = DetectLoop(head3);
     if ( result == TRUE )
     {    
       puts(pass);
     }
     else
     {
       printf("DetectLoopTrue Faild\n");
     }	
}

void DetectLoopTrue2()
{
     Person p , *head , p2 , *head2 , p3 , *head3 , *head4;
     int result;
     
     p.m_id = 3;
     strcpy(p.m_name , "amit");
     p.m_age = 15;

     p2.m_id = 2;
     strcpy(p2.m_name , "yarden");
     p2.m_age = 14; 

     p3.m_id = 1;
     strcpy(p3.m_name , "yosi");
     p3.m_age = 13; 
         
     head = ListInsertHead(NULL ,&p);
     head2 = ListInsertHead(head ,&p2);
     head3 = ListInsertHead(head2 ,&p3);
     
     DoLoop2(head3);
     result = DetectLoop(head3);
     if ( result == TRUE )
     {    
       puts(pass);
     }
     else
     {
       printf("DetectLoopTrue2 Faild\n");
     }	
}

void DetectLoopTrue3()
{
     Person p , *head , p2 , *head2 , p3 , *head3 , *head4;
     int result;
     
     p.m_id = 3;
     strcpy(p.m_name , "amit");
     p.m_age = 15;

     p2.m_id = 2;
     strcpy(p2.m_name , "yarden");
     p2.m_age = 14; 

     p3.m_id = 1;
     strcpy(p3.m_name , "yosi");
     p3.m_age = 13; 
         
     head = ListInsertHead(NULL ,&p);
     head2 = ListInsertHead(head ,&p2);
     head3 = ListInsertHead(head2 ,&p3);
     
     DoLoopHead(head3);
     result = DetectLoop(head3);
     if ( result == TRUE )
     {    
       puts(pass);
     }
     else
     {
       printf("DetectLoopTrue3 Faild\n");
     }	
}

void DetectLoopTrueEven()
{
     Person p , *head , p2 , *head2 ;
     int result;
     
     p.m_id = 3;
     strcpy(p.m_name , "amit");
     p.m_age = 15;

     p2.m_id = 2;
     strcpy(p2.m_name , "yarden");
     p2.m_age = 14; 
         
     head = ListInsertHead(NULL ,&p);
     head2 = ListInsertHead(head ,&p2);
     
     DoLoop(head2);
     result = DetectLoop(head2);
     if ( result == TRUE )
     {    
       puts(pass);
     }
     else
     {
       printf("DetectLoopTrueEven Faild\n");
     }
}

void DoLoop(Person *_head)
{
     Person *index = _head ;
     
	while ( index -> m_next != NULL )
	{
		index = index -> m_next ;
	}
	
	index -> m_next = _head ;

}

void DoLoop2(Person *_head)
{
     Person *index = _head ;
     
	while ( index -> m_next->m_next != NULL )
	{
		index = index -> m_next ;
	}
	
	index -> m_next = _head ;

}

void DoLoopHead(Person *_head)
{
	_head -> m_next = _head;
}
