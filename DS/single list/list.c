#include <stdio.h>
#include "list.h"

Person* ListInsertByKeyRecTwo(Person *_head, int _key , Person *_p);
Person* ListRemoveByKeyRecTwo(Person *_head , int _key , Person **_p);

Person* ListInsertHead(Person *_head ,Person *_p)
{
     if ( NULL == _p )
     {
          return _head;
     }    
     _p -> m_next = _head ;     
     return _p;
}

Person* ListRemoveHead(Person *_head ,Person **_item)
{
     if ( NULL == _head || NULL == _item )
     {    
          return _head ;
     }    
     *_item = _head ;
     return _head-> m_next;   
}

Person* ListInsertByKey(Person *_head, int _key, Person *_p)
{
     Person *tmp , *prev;
     
     if ( NULL == _p )
     {
     return _head; 
     }
     if ( NULL == _head ||  _head -> m_id > _key )
     {
     _p -> m_next = _head;
     return _p ;
     }
        
     tmp = _head ;
     prev = _head;
     
     while( tmp -> m_id <= _key )
     {
          if ( tmp -> m_id == _key )
          {
               return _head ;
          }
          if ( NULL == tmp -> m_next )
          {
               tmp -> m_next = _p ;
               _p -> m_next = NULL ;
               return _head ;
          } 
          prev = tmp;
          tmp =tmp -> m_next;
     }
     
     _p -> m_next = prev->m_next ;
     prev->m_next = _p ;
     return _head;
}

Person* ListInsertByKeyRec(Person *_head, int _key , Person *_p)
{
     if ( NULL == _p )
     {
     return _head; 
     } 

          return ListInsertByKeyRecTwo(_head, _key ,_p);
            
}

Person* ListInsertByKeyRecTwo(Person *_head, int _key , Person *_p)
{
          if ( NULL == _head || _head ->  m_id > _key  )
          {
           _p -> m_next = _head  ;
           _head = _p ;
           return _head;
          } 
          if ( _head -> m_id == _key )
          {
               return _head ;
          }
       
      _head -> m_next = ListInsertByKeyRecTwo( _head -> m_next,  _key ,_p) ;
      return _head ;
}

Person* ListRemoveByKey(Person *_head , int _key , Person **_p)
{
     Person *tmp , *prv;
     
     if ( NULL == _head || NULL == _p )
     {
          return _head ;
     } 
     
     if ( _head -> m_id == _key)
     {
          *_p = _head ;
          _head = _head -> m_next ;
          return _head;
     }
     
     for ( tmp = _head , prv = _head ; tmp != NULL ; tmp = tmp -> m_next )
     {
          if ( tmp -> m_id == _key)
          {
               *_p = tmp ;
               prv -> m_next = tmp -> m_next ;
               return _head ;
          }         
          prv = tmp;
     }
     
     *_p = NULL ;
     return _head ;
}

Person* ListRemoveByKeyRec(Person *_head , int _key , Person **_p)
{
     if ( NULL == _head || NULL == _p )
     {
          return _head ;
     } 
     else
     {
          return ListRemoveByKeyRecTwo(_head , _key ,_p);
     }     
}
Person* ListRemoveByKeyRecTwo(Person *_head , int _key , Person **_p)
{
          if ( NULL == _head || _head->m_id > _key)
          {
               return _head ;
          }     
          if ( _head -> m_id == _key)
          {
               *_p = _head ;
               _head  = _head  -> m_next;
               return _head ;
          }     

     _head -> m_next = ListRemoveByKeyRecTwo(_head -> m_next , _key ,_p);
     return _head ;
}

void PrintList(Person *_head)
{
     Person *index;
     
     for ( index = _head ; index != NULL ; index = index -> m_next)
     {
          printf("%d , %s , %d \n" , index -> m_id , index -> m_name , index -> m_age);
     }
}

Person* Flip(Person *_head)
{
     Person *tmp;
     
     if( NULL == _head || NULL == _head->m_next )
     {
          return _head;
     }
     
     tmp = Flip(_head->m_next);
     
     _head->m_next->m_next=_head;
     _head->m_next=NULL;
     
     return tmp;
}

int DetectLoop(Person *_head)
{
	Person *slowPtr = _head , *fastPtr = _head ;	
	
	while ( slowPtr && fastPtr && fastPtr->m_next )
	{
	   slowPtr = slowPtr->m_next ;
	   fastPtr = fastPtr->m_next->m_next ;
	   if ( slowPtr == fastPtr )
	   {
	   	return TRUE ;
	   }
	}
	
	return FALSE;
}



