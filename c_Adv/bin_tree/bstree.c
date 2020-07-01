#include <stdio.h> 
#include <stdlib.h>  /* malloc */
#include <limits.h>
#include "bstree.h"


#define MAGIC_NUM 0XBEEFBEEF
#define IS_EQULE(x,y) (x==y)
#define DATA_EXIST 0
#define FINISH 1
#define RIGHT(node) ( node -> m_right )
#define LEFT(node) ( node -> m_left )
#define FALSE 0

typedef struct Node Node;

struct Node 
{
     void* m_item;
     Node* m_right;
     Node* m_left;
     Node* m_father;
};  

struct BSTree
{
     size_t         m_magicNum;
     Node           m_sentinel;
     LessComparator m_less;
};        


static Node *faultItr;


/* ------------------------------------------------------- local function ------------------------------------------------------------------------- */
static void DeleteAllNodes(Node* _node ,  void (*_destroyer)(void*) , Node* _sentinel );
static int FindFatherOrFindData( Node **_ptrFather , void* _item , LessComparator _less  , Node *_sentinel);
static BSTreeItr InsertRoot(BSTree* _tree , Node *_node , void* _item);
static BSTreeItr FinalInsert(Node *_newNode , Node *_ptrFather , void* _item , LessComparator _less);   
static Node* CreateNode(void* _item, BSTree* _tree);
static void DestroyWithoutFunc(Node *_node, Node* _sentinel);
static void DestroyWithFunc(Node *_node ,void (*_destroyer)(void*), Node* _sentinel);
static void InOrderRec(Node *_node , Node* _sentinel);
static BSTreeItr PreEach(Node *_node , ActionFunction _action, void* _context );
static BSTreeItr InEach(Node *_node , ActionFunction _action, void* _context );
static BSTreeItr PostEach(Node *_node , ActionFunction _action, void* _context );

/*==================================================================================================================================================*/
/*============================================================= API ================================================================================*/
/*==================================================================================================================================================*/

/* --------------------------------------------------------- BSTree Create ------------------------------------------------------------------------ */
BSTree* BSTreeCreate(LessComparator _less)
{
     BSTree *ptrTree ;
     
     
	if ( NULL == _less )
	{
		return NULL;
	}
     
     if( (ptrTree = (BSTree*)calloc(1 ,sizeof(BSTree))) == NULL )
     {
          return NULL ;
     }
     
     ptrTree->m_sentinel.m_father = &(ptrTree->m_sentinel);
     ptrTree->m_sentinel.m_right  = &(ptrTree->m_sentinel);
     ptrTree->m_sentinel.m_left   = &(ptrTree->m_sentinel);     
     ptrTree->m_less              = _less;
     ptrTree->m_magicNum          = MAGIC_NUM;
     
     return ptrTree;
}

/* -------------------------------------------------------- BSTree Destroy ------------------------------------------------------------------------ */
void  BSTreeDestroy(BSTree* _tree, void (*_destroyer)(void*))
{
     if ( NULL == _tree || (_tree->m_magicNum != MAGIC_NUM) )
     {
          return;
     }
     
     _tree->m_magicNum = 0XDEADBEEF ; 
        
     DeleteAllNodes(_tree-> m_sentinel.m_left , _destroyer , &_tree-> m_sentinel); 
        
     free(_tree);
     
     return;
}

/* -------------------------------------------------------- Tree Insert --------------------------------------------------------------------------- */
BSTreeItr BSTreeInsert(BSTree* _tree, void* _item)
{
     Node *ptrNewNode , *ptrFather;
     int result;
     
     if ( NULL == _tree || NULL == _item || (_tree->m_magicNum != MAGIC_NUM) )
     {
          return NULL;
     }
   
     if ((ptrNewNode = CreateNode(_item , _tree)) == NULL )
     {
          return (BSTreeItr)&_tree->m_sentinel;
     }
     
     if ( _tree -> m_sentinel.m_left == &(_tree->m_sentinel))
     {
          return InsertRoot(_tree, ptrNewNode , _item);               
     } 
   
     ptrFather =  _tree -> m_sentinel.m_left;
	_tree -> m_sentinel.m_item = _item;
	
     if ((result=FindFatherOrFindData( &ptrFather ,  _item , _tree->m_less , &_tree -> m_sentinel )) == DATA_EXIST)
      {
        free(ptrNewNode);
        return (BSTreeItr)ptrFather;
      }
      
      _tree -> m_sentinel.m_item = NULL;

     return FinalInsert(ptrNewNode , ptrFather , _item , _tree->m_less);                  
}

/* ------------------------------------------------------ BSTree Itr Begin ------------------------------------------------------------------------ */
BSTreeItr BSTreeItrBegin(const BSTree* _tree)
{
	Node *node , *begin;
	
	if ( NULL == _tree )
	{
		return (BSTreeItr)faultItr ;
	}
	
	node = _tree->m_sentinel.m_left ;
	begin = _tree->m_sentinel.m_left ;
		
	while ( node != &_tree->m_sentinel )
	{
		begin = node ;
		node = node -> m_left;
	}
		
	return (BSTreeItr)begin;	
}

/* ---------------------------------------------------- BSTree Itr End ---------------------------------------------------------------------------- */
BSTreeItr BSTreeItrEnd(const BSTree* _tree)
{
	Node *node , *end;
	
	if ( NULL == _tree )
	{
		return (BSTreeItr)faultItr ;
	}
	
	node = _tree->m_sentinel.m_left ;
	end = _tree->m_sentinel.m_left ;
		
	while ( node != &_tree->m_sentinel )
	{
	    end = node ;
	    node = node -> m_right;
	}
		
	return (BSTreeItr)end;	
}

/* -------------------------------------------------- BSTree Itr Equals --------------------------------------------------------------------------- */
int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
	return IS_EQULE(_a , _b);
}

/* --------------------------------------------------- BSTree Itr Get ----------------------------------------------------------------------------- */
void* BSTreeItrGet(BSTreeItr _it)
{
	return  ((Node*)_it)->m_item;
}

/* --------------------------------------------------- Is Fault Itr ------------------------------------------------------------------------------- */
int IsFaultItr(BSTreeItr _it)
{
	return IS_EQULE( _it , (BSTreeItr)faultItr);
}


/* -------------------------------------------------- BSTreeItrNext ------------------------------------------------------------------------------- */
BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
	Node* node = ((Node*)_it)->m_right;
	Node* node2 ;
	if ( node->m_item != NULL )
	{
		while ( node->m_item != NULL)
		{
			node2 = node ;
			node = node->m_left ;
		}
		return (BSTreeItr)node2;
	}
	else
	{
		node = ((Node*)_it)->m_father;
		node2 = ((Node*)_it);
		while ( ((*(int*)node->m_item) < (*(int*)node2->m_item) ) && (node->m_item != NULL) )
		{
			node = node->m_father;
		}
		
		return (BSTreeItr)node;
	}
}


/* ------------------------------------------------- BSTreeItrPrev -------------------------------------------------------------------------------- */
BSTreeItr BSTreeItrPrev(BSTreeItr _it)
{
	Node* node = ((Node*)_it)->m_left;
	Node* node2 ;
	if ( node->m_item != NULL )
	{
		while ( node->m_item != NULL)
		{
			node2 = node ;
			node = node->m_right ;
		}
		return (BSTreeItr)node2;
	}	
	else
	{
		node = ((Node*)_it)->m_father;
		node2 = ((Node*)_it);
		while ( ((*(int*)node->m_item) > (*(int*)node2->m_item) ) && (node->m_item != NULL) )
		{
			node = node->m_father;
		}
		
		return (BSTreeItr)node;
	}		
}

/* ------------------------------------------------------- BSTree Find First ---------------------------------------------------------------------- */
BSTreeItr BSTreeFindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
	BSTreeItr begin =  BSTreeItrBegin(_tree);

	while ( ((Node*)begin) -> m_item != NULL )
	{
		if ( _predicate( ((Node*)begin)->m_item , _context ) == 0 )
		{
			return begin;
		}
		begin = BSTreeItrNext(begin);
	}
	return begin;
}


/* ------------------------------------------------------- BSTree For Each ------------------------------------------------------------------------ */
BSTreeItr BSTreeForEach(const BSTree* _tree, TreeTraversalMode _mode, ActionFunction _action, void* _context)
{
	switch(_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER :
									return PreEach(_tree->m_sentinel.m_left , _action , _context );
									break;
		case BSTREE_TRAVERSAL_INORDER  :
									return InEach(_tree->m_sentinel.m_left , _action , _context );
									break;		
		case BSTREE_TRAVERSAL_POSTORDER:
									return PostEach(_tree->m_sentinel.m_left , _action , _context );
									break;			
		default:
		         break;
	}
	return (BSTreeItr)faultItr;
}

/*==================================================================================================================================================*/
/*========================================================== local function ========================================================================*/
/*==================================================================================================================================================*/

/* ------------------------------------------------------- Delete All Nodes ----------------------------------------------------------------------- */
static void DeleteAllNodes(Node* _node ,  void (*_destroyer)(void*), Node* _sentinel )
{
	if ( _node != NULL )
	{
		if ( NULL == _destroyer )
		{
			DestroyWithoutFunc(_node , _sentinel);
		}
		else
		{
			DestroyWithFunc(_node , _destroyer , _sentinel);
		}
	}	
	return;
}

/* ----------------------------------------------------- Destroy Without Func --------------------------------------------------------------------- */
static void DestroyWithoutFunc(Node *_node, Node* _sentinel)
{
     if ( _node == _sentinel)
     {
          return;
     }    

     DestroyWithoutFunc( _node->m_left , _sentinel ); 
     DestroyWithoutFunc( _node->m_right , _sentinel );        
     free( _node );
}

/* ------------------------------------------------------ Destroy With Func ----------------------------------------------------------------------- */
static void DestroyWithFunc(Node *_node ,void (*_destroyer)(void*), Node* _sentinel)
{
     if ( _node == _sentinel)
     {
          return;
     }    
     DestroyWithFunc( _node->m_right , _destroyer , _sentinel );
     DestroyWithFunc( _node->m_left , _destroyer , _sentinel );
     _destroyer( _node->m_item); 
     free( _node );
}

/* ----------------------------------------------------------- Insert Root ------------------------------------------------------------------------ */
static BSTreeItr InsertRoot(BSTree* _tree , Node *_node , void* _item)
{
         _node->m_item   = _item ;
         _node->m_right  = &_tree->m_sentinel ;  
         _node->m_left   = &_tree->m_sentinel ; 
         _node->m_father = &_tree->m_sentinel ;
         _tree -> m_sentinel.m_left = _node ;
         return (BSTreeItr)_node ;   
}

/* --------------------------------------------------- Find Father Or Find Data --------------------------------------------------------------------*/
static int FindFatherOrFindData( Node **_ptrFather , void* _item , LessComparator _less  , Node *_sentinel)
{
     Node *ptrTemp = *_ptrFather;
     
     while ( !(IS_EQULE(ptrTemp , _sentinel)) )
     {
          *_ptrFather =  ptrTemp ;    
          
          if ( _less( ptrTemp->m_item , _item ) )  
          {
             ptrTemp = ptrTemp->m_right ;
          }         
          else if ( _less(  _item , ptrTemp->m_item ) )   
          {
             ptrTemp = ptrTemp->m_left ;
          } 
          else
          {
            return DATA_EXIST ;
          }
      }
   return FINISH;
}

/* -------------------------------------------------------- Final Insert -------------------------------------------------------------------------- */
static BSTreeItr FinalInsert(Node *_newNode , Node *_ptrFather , void* _item , LessComparator _less )
{
     _newNode->m_father = _ptrFather;

     if ( _less( _ptrFather->m_item , _item ) )
     {
        _ptrFather -> m_right = _newNode;  
     }
     else
     {
        _ptrFather -> m_left = _newNode;  
     }
     
     return (BSTreeItr)_newNode;
}

/* --------------------------------------------------------- Create Node --------------------------------------------------------------------------- */
static Node* CreateNode(void* _item , BSTree* _tree)
{
	Node *ptrNewNode;

     if( (ptrNewNode = (Node*)calloc(1,sizeof(Node))) == NULL )
     {
          return NULL;
     }

	ptrNewNode->m_item  = _item;
	ptrNewNode->m_left  = &_tree->m_sentinel;
	ptrNewNode->m_right = &_tree->m_sentinel;
		
	return ptrNewNode;
}

/* ---------------------------------------------------------- In Order  --------------------------------------------------------------------------- */
void InOrder(BSTree *_tree)
{
	InOrderRec(_tree->m_sentinel.m_left , &_tree->m_sentinel );
}
/* -------------------------------------------------------- In Order Rec -------------------------------------------------------------------------- */
static void InOrderRec(Node *_node , Node* _sentinel)
{
     if ( _sentinel == _node )
     {
          return;
     }
          
     InOrderRec(_node->m_left , _sentinel);     
     printf ("%d " , *(int*)_node->m_item);          
     InOrderRec(_node->m_right , _sentinel);
}

/* --------------------------------------------------------- PreEach ------------------------------------------------------------------------------ */
static BSTreeItr PreEach(Node *_node , ActionFunction _action, void* _context )
{
	if ( _node->m_item == NULL )
	{
		return (BSTreeItr)_node;
	}
	
	if ( _action(_node->m_item , _context) )
	{
		return (BSTreeItr)_node;		
	} 
	
     PreEach(_node->m_left , _action , _context );
	return PreEach(_node->m_right , _action , _context );	

}

/* --------------------------------------------------------- InEach ------------------------------------------------------------------------------- */
static BSTreeItr InEach(Node *_node , ActionFunction _action, void* _context )
{
	if ( _node->m_item == NULL )
	{
		return (BSTreeItr)_node;
	}
	
	InEach(_node->m_left , _action , _context );
	
	if ( _action(_node->m_item , _context) )
	{
		return (BSTreeItr)_node;		
	} 	
	
	return InEach(_node->m_right , _action , _context );
}

/* --------------------------------------------------------- PostEach ----------------------------------------------------------------------------- */
static BSTreeItr PostEach(Node *_node , ActionFunction _action, void* _context)
{
	if ( _node->m_item == NULL )
	{
		return (BSTreeItr)_node;
	}
	
	PostEach(_node->m_left , _action , _context );
	
	return PostEach(_node->m_right , _action , _context );
	
	if ( _action(_node->m_item , _context) )
	{
		return (BSTreeItr)_node;		
	} 		
}


