
#include "list_functions.h"

#define SWAP(tmpbegin , next , data) ( ListItrSet(tmpbegin,ListItrSet(next, data)) )

void ListItrBubbleSort(ListItr _begin, ListItr _end, LessFunction _less)
{
    int change=1 ;
    ListItr next , tmpbegin , tmpend ;
    int *data , *dataNext ;
    
    if ( NULL == _begin || NULL == _end || NULL == _less )
    {
      return ;
    }

    tmpend =  _end ;
         
    while(change)
    {     
       for( tmpbegin = _begin , next = ListItrNext(_begin) , change=0 ; next != tmpend ;   )
       {
       	data = ListItrGet(tmpbegin);
       	dataNext = ListItrGet(next); 
       	      	
          if( _less(data ,dataNext ) )
          {
              SWAP(tmpbegin , next , data );
              change=1;
          }
          tmpbegin = next ;
          next = ListItrNext(next);
          
       }              
       tmpend = ListItrPrev(tmpend); 
    }
    
    return ;    
}


void ListItrShakeSort(ListItr _begin, ListItr _end, LessFunction _less)
{
    int change=1 ;
    ListItr next , tmpbegin , tmpend ;
    int *data , *dataNext ;
    
    if ( NULL == _begin || NULL == _end || NULL == _less )
    {
      return ;
    }

    tmpend =  _end ;
         
    while(change)
    {     
       for( tmpbegin = _begin , next = ListItrNext(_begin) , change=0 ; next != tmpend ;   )
       {
       	data = ListItrGet(tmpbegin);
       	dataNext = ListItrGet(next); 
       	      	
          if( _less(data ,dataNext ) )
          {
              SWAP(tmpbegin , next , data );
              change=1;
          }
          tmpbegin = next ;
          next = ListItrNext(next);
          
       }              
       tmpend = ListItrPrev(tmpend);
       
       if ( change)
       {
       	for ( next = ListItrPrev(next) , tmpbegin = ListItrPrev(tmpbegin) ; next != _begin ; )
       {
       	data = ListItrGet(tmpbegin);
       	dataNext = ListItrGet(next); 
       	      	
          if( _less(data ,dataNext ) )
          {
              SWAP(tmpbegin , next , data );
              change=1;
          }
          tmpbegin = next ;
          next = ListItrNext(next);
          
       }              
       _begin = ListItrNext(_begin);
       } 
    }
    
    return ; 
}

ListItr ListItrSplice(ListItr _dest, ListItr _begin, ListItr _end)
{
	ListItr next ;
		
	while ( _end != _begin )
	{
		next = ListItrNext(_begin);
		ListItrInsertBefore( _dest , ListItrRemove(_begin));
		_begin = next;	
	}
	return _begin;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	void *item;
	while (_begin != _end )
	{
		item = ListItrGet(_begin);
		if ( _action(item,_context) == 0)
		{
			return _begin;
		}
		_begin = ListItrNext(_begin);
	}
	return _begin;
}


ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	void *item;
	while (_begin != _end )
	{
		item = ListItrGet(_begin);
		if ( _predicate(item,_context) )
		{
			return _begin;
		}
		_begin = ListItrNext(_begin);
	}
	return _begin;
}




