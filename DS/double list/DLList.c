#include <stdlib.h> /* allocation */
#include "DLList.h"
#include "list_itr.h"

#define MAGIC_NUM 0XBEEFBEEF
#define IS_EQUALS(_a ,_b) ((_a)==(_b) )
#define NODE(_itr) ( ((Node*)_itr) )
  

typedef struct Node Node;

struct Node
{
     void* m_data;
     Node* m_next;
     Node* m_prev;
};

struct List
{
     int m_magicNum;
     Node m_head;
     Node m_tail;
};

/*------------------------- local function---------------------------*/
static ListResult Push(Node *_headOrTail ,Node *_ptrNode);
static Node* Pop(Node *_headOrTail);
static void InitList(List *_list);
static void DestroyEelementWithFunc(List* _pList, void (*_elementDestroy)(void* _item));
static void DestroyEelementWithoutFunc(List* _pList);
static ListResult CheckPushParam(List* _list, void* _item);  
static ListResult CheckPopParam(List* _list, void** _pItem);
static void DestroyAllNodes(List* _pList, void (*_elementDestroy)(void* _item));
static Node* CreateNode(void* _item); 	
static void* DestroyNode(Node *_node);  

/*==================================================================================================================================================*/
/* ============================================================ API =============================================================================== */
/*==================================================================================================================================================*/

/*----------------------------- List Create ------------------------- */
List* ListCreate(void)
{
     List *ptrList;
     
     ptrList = (List*)calloc(1 , sizeof(List));  
     if ( NULL == ptrList )
     {
          return NULL;
     }         

	InitList( ptrList ) ;    
	 
     ptrList->m_magicNum = MAGIC_NUM;   
     
     return ptrList;
}
/*---------------------------------------------------------- List Destroy ------------------------------------------------------------------------*/
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{    
     if ( !_pList || !*_pList || !((*_pList)->m_magicNum == MAGIC_NUM) )
     {
     	return; 
     } 
     
     (*_pList)->m_magicNum = 0XDEADBEEF;    

     DestroyAllNodes( *_pList , _elementDestroy );	
     
     free(*_pList);
     *_pList = NULL ;
     
     return;
}
/* ---------------------------------------------------- List Push Head ---------------------------------------------------------------------------- */
ListResult ListPushHead(List* _list, void* _item)
{
     Node *ptrNode;
     ListResult result ;

     result = CheckPushParam( _list, _item );  
	if ( result != LIST_SUCCESS )
	{
		return result;
	}

     ptrNode = CreateNode(_item);       
     
     return Push(_list->m_head.m_next ,ptrNode);     
}
/* -------------------------- List Push Tail ------------------------ */
ListResult ListPushTail(List* _list, void* _item)
{
     Node *ptrNode;
     ListResult result ;

     result = CheckPushParam( _list, _item );  
	if ( result != LIST_SUCCESS )
	{
		return result;
	}
     
     ptrNode = CreateNode(_item);       
     
     return Push(&_list->m_tail ,ptrNode);
}
/* -------------------------- List Pop Head -------------------------- */
ListResult ListPopHead(List* _list, void** _pItem)
{
	Node *ptrNodeDelete;
	
     ListResult result ;
     
     result = CheckPopParam( _list, _pItem );
	if ( result != LIST_SUCCESS )
	{
		return result;
	}	
     
     ptrNodeDelete = Pop(_list->m_head.m_next);
     
     *_pItem = DestroyNode(ptrNodeDelete);     
     
     return LIST_SUCCESS;
}
/* --------------------------- List Pop Tail ------------------------ */
ListResult ListPopTail(List* _list, void** _pItem)
{
     ListResult result ;
     Node *ptrNodeDelete;
     
     result = CheckPopParam( _list, _pItem );
	if ( result != LIST_SUCCESS )
	{
		return result;
	}
     
     ptrNodeDelete = Pop(_list->m_tail.m_prev);

     *_pItem = DestroyNode(ptrNodeDelete);  
     
     return LIST_SUCCESS;
}
/* --------------------------- List Size ---------------------------- */
size_t ListSize(const List* _list)
{
     size_t size = 0;
     Node *index ;
     
     if ( _list != NULL && (_list->m_magicNum == MAGIC_NUM) )
     {
        for ( index = _list->m_head.m_next ; index != &(_list->m_tail) ; index = index->m_next )
        {
           size++;
        } 
     }    
     return size;
}


/*=====================================================================*/
/*============================ local function =========================*/
/*=====================================================================*/

/* ------------------------------- Push ----------------------------- */ 
static ListResult Push(Node *_headOrTail ,Node *_ptrNode)
{
     if ( NULL == _ptrNode )
     {
          return LIST_ALLOCATION_ERROR;
     }
     
     _ptrNode->m_prev =  _headOrTail-> m_prev;
     _ptrNode->m_next =  _headOrTail ;
     _headOrTail -> m_prev ->m_next = _ptrNode;
     _headOrTail -> m_prev= _ptrNode ;
     return LIST_SUCCESS;
   
}
/*------------------------------- Pop -------------------------------*/
static Node* Pop(Node *_headOrTail)
{
     _headOrTail->m_next->m_prev = _headOrTail->m_prev;
     _headOrTail->m_prev->m_next = _headOrTail->m_next;    

     return _headOrTail;
}
/*---------------------------- Init List -----------------------------*/
static void InitList(List *_list)
{
     _list->m_head.m_next = &(_list->m_tail) ; 
     _list->m_head.m_prev = &(_list->m_head) ;
     _list->m_tail.m_next = &(_list->m_tail) ;
     _list->m_tail.m_prev = &(_list->m_head) ;
     return;  
}
/*------------------------------------------------- Destroy Eelement With Func ---------------------------------------------------------------------*/
static void DestroyEelementWithFunc(List* _pList, void (*_elementDestroy)(void* _item))
{
  Node *currNode = _pList -> m_head.m_next ;
  Node *nextNode = _pList -> m_head.m_next->m_next ;
	
  if ( currNode != &((_pList)->m_tail) )
  {    
    for( ; nextNode != &(_pList->m_tail) ; nextNode = nextNode->m_next)
       {
           _elementDestroy(DestroyNode(currNode));     
          currNode = nextNode;
       }
       _elementDestroy(DestroyNode(currNode));  
   }
   return; 
}
/*------------------------------------------------- Destroy Eelement Without Func ------------------------------------------------------------------*/
static void DestroyEelementWithoutFunc(List* _pList)
{
  Node *currNode = _pList -> m_head.m_next ;
  Node *nextNode = _pList -> m_head.m_next->m_next ;
	
  if ( currNode != &((_pList)->m_tail) )
  {    
    for( ; nextNode != &(_pList->m_tail) ; nextNode = nextNode->m_next)
       {     
          DestroyNode(currNode);
          currNode = nextNode;
       }
       DestroyNode(currNode);
   }
   return;
}


/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
static ListResult CheckPushParam(List* _list, void* _item)
{
     if ( NULL == _list || !(_list->m_magicNum == MAGIC_NUM) )
     {
          return LIST_UNINITIALIZED_ERROR;
     }
     
     if ( NULL == _item )
     {
     	return LIST_NULL_ELEMENT_ERROR;
     }
     
     return LIST_SUCCESS;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
static ListResult CheckPopParam(List* _list, void** _pItem)
{
     if ( NULL == _list || !(_list->m_magicNum == MAGIC_NUM) )
     {
          return LIST_UNINITIALIZED_ERROR;
     }

     if ( NULL == _pItem )
     {
     	return LIST_NULL_ELEMENT_ERROR;
     }
          
     if ( _list->m_head.m_next == &_list->m_tail)
     {
          return LIST_UNDERFLOW_ERROR;
     }
     
     return LIST_SUCCESS;
}

/* --------------------------------------------------- Destroy All Nodes --------------------------------------------------------------------------*/
static void DestroyAllNodes(List* _pList, void (*_elementDestroy)(void* _item))
{
	if ( _elementDestroy != NULL )
	{
		DestroyEelementWithFunc( _pList , _elementDestroy );
     }
     else
     {
     	DestroyEelementWithoutFunc( _pList );
     }
}

/* ------------------------------------------------------ Create Node ------------------------------------------------------------------------------*/
static Node* CreateNode(void* _item)
{
	Node *ptrNode;
	
     ptrNode = (Node*)calloc(1,sizeof(Node));   
     if ( NULL == ptrNode )
     {
          return NULL;
     }
     
     ptrNode->m_data = _item;	
     return ptrNode;
}


/* ------------------------------------------------------ Destroy Node -----------------------------------------------------------------------------*/
static void* DestroyNode(Node *_node)
{
	void* data;
	data = _node->m_data;
	free(_node);
	return data;
}  

/*==================================================================================================================================================*/
/* ======================================================= List Itr func ========================================================================== */
/*==================================================================================================================================================*/

/* ------------------------------------------------------- List Itr Begin ------------------------------------------------------------------------- */
ListItr ListItrBegin(const List* _list)
{
	if ( NULL == _list || !(_list->m_magicNum == MAGIC_NUM) )
	{
		return NULL ;
	}
	 return (ListItr)_list->m_head.m_next ;
}

/* ------------------------------------------------------- List Itr End ------------------------------------------------------------------------- */
ListItr ListItrEnd(const List* _list)
{
	if ( NULL == _list || !(_list->m_magicNum == MAGIC_NUM) )
	{
		return NULL ;
	}
	return (ListItr)&_list->m_tail ;
}

/* ------------------------------------------------------- List Itr Equals ------------------------------------------------------------------------ */
int ListItrEquals(const ListItr _a, const ListItr _b)
{
	return IS_EQUALS(_a , _b);
}

/* ------------------------------------------------------- List Itr Next ------------------------------------------------------------------------- */
ListItr ListItrNext(ListItr _itr)
{
	return (ListItr)((Node*)_itr)->m_next ;
}

/* ------------------------------------------------------- List Itr Prev ------------------------------------------------------------------------- */
ListItr ListItrPrev(ListItr _itr)
{
	return (ListItr)((Node*)_itr)->m_prev->m_prev->m_next ;
}

/* ------------------------------------------------------- List Itr Get ------------------------------------------------------------------------- */
void* ListItrGet(ListItr _itr)
{
	return ((Node*)_itr)->m_data ;
}

/* ------------------------------------------------------ List Itr Set ---------------------------------------------------------------------------- */
void* ListItrSet(ListItr _itr, void* _element)
{
	 void* data;
	
	 data = NODE(_itr)->m_data ;
	 
	 ((Node*)_itr)->m_data = _element;
	 
	 return data;
}

/* ------------------------------------------------------ List Insert Before ---------------------------------------------------------------------- */
ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
     Node *ptrNode;
     
     ptrNode = CreateNode(_element);   
     
     Push((Node*)_itr ,ptrNode); 
          
	return (ListItr)ptrNode;
}

/* ------------------------------------------------------ List Itr Remove ------------------------------------------------------------------------- */
void* ListItrRemove(ListItr _itr)
{
	Node *ptrNode;
		
	ptrNode = Pop((Node*)_itr);  
	
	return DestroyNode(ptrNode); 
}

