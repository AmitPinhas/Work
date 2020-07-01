
#include "bonus.h"

static void PreOrderRec(Node *_node);
static void InOrderRec(Node *_node);
static void PostOrderRec(Node *_node);
static int IsFullTreeRec(Node *_node);       
static int AreSimilarRec(Node *_nodeOne ,Node *_nodeTwo ); 
static int IsPerfectTreeRec(Node *_nodeOne , Node *_nodeTwo);
static int IsBSTUtil(Node *_node , int min , int max);

/* -------------------------------------------------------- Tree Print ---------------------------------------------------------------------------- */
void TreePrint(const BSTree* _tree , TreeTraversalMode _traverseMode)
{
     if ( NULL == _tree )
     {
          return ;
     }
     
     switch(_traverseMode)
     {
          case BSTREE_TRAVERSAL_PREORDER:
                       PreOrderRec(_tree->m_root);
                       break;
                       
          case BSTREE_TRAVERSAL_INORDER:
                       InOrderRec(_tree->m_root);
                       break;
                         
          case BSTREE_TRAVERSAL_POSTORDER:
                       PostOrderRec(_tree->m_root);
                       break;
                         
          default:
                  break;                                             
     }
     putchar('\n');
}


/* ------------------------------------------------------- Is Full Tree --------------------------------------------------------------------------- */
int IsFullTree(const BSTree* _tree)
{
	if ( NULL == _tree )
	{
		return FALSE;
	}
	
	return IsFullTreeRec(_tree->m_root);
}

int AreSimilar(const BSTree* _treeOne ,const Tree* _treeTwo)
{
	if ( (NULL == _treeOne) && (NULL==_treeTwo) )
	{
		return FALSE;
	}
	if ( ((NULL != _treeOne) && (NULL==_treeTwo) ) || ((NULL == _treeOne) && (NULL!=_treeTwo) ) )
	{
		return FALSE;
	}
	
	return AreSimilarRec(_treeOne->m_root ,_treeTwo->m_root );
}


/* ----------------------------------------------------- Is Perfect Tree -------------------------------------------------------------------------- */
int IsPerfectTree(const BSTree* _tree)
{
	if ( NULL == _tree )
	{
		return FALSE;
	}
	
	return IsPerfectTreeRec(_tree->m_root , _tree->m_root);
}

int IsBST(const BSTree* _tree)
{
	if ( NULL == _tree )
	{
		return FALSE_BST ;
	}
	
	return(IsBSTUtil(_tree->m_root , INT_MIN , INT_MAX)); 
}


/* -------------------------------------------------------- Pre Order Rec ------------------------------------------------------------------------- */
static void PreOrderRec(Node *_node)
{
     if ( NULL == _node )
     {
          return;
     }
     
     printf ("%d " , _node->m_data);    
     PreOrderRec(_node->m_left);
     PreOrderRec(_node->m_right);
}

/* -------------------------------------------------------- In Order Rec -------------------------------------------------------------------------- */
static void InOrderRec(Node *_node)
{
     if ( NULL == _node )
     {
          return;
     }
          
     InOrderRec(_node->m_left);     
     printf ("%d " , _node->m_data);          
     InOrderRec(_node->m_right);
}

/* -------------------------------------------------------- Post Order Rec ------------------------------------------------------------------------ */
static void PostOrderRec(Node *_node)
{
     if ( NULL == _node )
     {
          return;
     }
          
     PostOrderRec(_node->m_left);        
     PostOrderRec(_node->m_right);
     printf ("%d " , _node->m_data); 
}


/* ------------------------------------------------------ Is Full Tree Rec ------------------------------------------------------------------------ */
static int IsFullTreeRec(Node *_node)
{
	int result ;
	
     if ( NULL == _node )
     {
          return TRUE ;
     }
          
     result = IsFullTreeRec(_node->m_left);        
     result = IsFullTreeRec(_node->m_right);
     
     if ( ((_node->m_right!=NULL) && (_node->m_left==NULL)) ||  ((_node->m_right==NULL) && (_node->m_left!=NULL)) )
     {
         result= FALSE;
     }
     
     return result;
}

/* ---------------------------------------------------- Are Similar Rec --------------------------------------------------------------------------- */
static int AreSimilarRec(Node *_nodeOne ,Node *_nodeTwo )
{
	int result ;
	
	if(result == FALSE)
	{
		return FALSE;
	}
	
     if ( (NULL == _nodeOne) && (NULL==_nodeTwo ) )
     {
          return TRUE ;
     }

     if ( ((NULL != _nodeOne) && (NULL==_nodeTwo )) || ((NULL == _nodeOne) && (NULL!=_nodeTwo )) )
     {
	     return FALSE;
     }

     result = AreSimilarRec(_nodeOne->m_left ,_nodeTwo->m_left );        
     result = AreSimilarRec(_nodeOne->m_right ,_nodeTwo->m_right );

	
     if ( ((_nodeOne->m_right==NULL) && (_nodeTwo->m_right!=NULL)) || ((_nodeOne->m_right!=NULL) && (_nodeTwo->m_right==NULL)) ||  ((_nodeOne->m_left==NULL) && (_nodeTwo->m_left!=NULL)) || ((_nodeOne->m_left!=NULL) && (_nodeTwo->m_left==NULL)) )
     {
         result = FALSE;
     }     

     return result;
}

/* ------------------------------------------------- Is Perfect Tree Rec -------------------------------------------------------------------------- */
static int IsPerfectTreeRec(Node *_nodeOne , Node *_nodeTwo)
{
	int result;

	if ( (NULL != _nodeOne && NULL == _nodeTwo) || (NULL == _nodeOne && NULL != _nodeTwo) || (result == FALSE) )
	{
		return FALSE;
	}	
	
	if ( NULL == _nodeOne && NULL == _nodeTwo)
	{
		return TRUE;
	}
	
    result = IsPerfectTreeRec(_nodeOne->m_left , _nodeTwo->m_right);
    result =  IsPerfectTreeRec(_nodeOne->m_right , _nodeTwo->m_left);
    
    return result;	
}

/* --------------------------------------------------- Is BST Util -------------------------------------------------------------------------------- */
static int IsBSTUtil(Node *_node , int min , int max)
{
	if ( NULL == _node )
	{
		return TRUE ;
	}
	
	if ( (_node->m_data < min) || (_node->m_data > max) )
	{
		return FALSE_BST ;
	}
	
	return ( (IsBSTUtil(_node->m_left , min , _node->m_data-1 )) && (IsBSTUtil(_node->m_right , _node->m_data+1 , max ))) ;
}


/* ********************Is Full Tree Test**************************** */

static void IsFullTreeFalse()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsFullTreeFalse:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50); 
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 55);
     
     result = IsFullTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsFullTreeTrue()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsFullTreeTrue:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 45);      
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);
     
     result = IsFullTree(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsFullTreeNull()
{
	int result;
	     
     printf("IsFullTreeNull:   ");	
   
     result = IsFullTree(NULL); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
}

static void IsFullTreeEmpty()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsFullTreeEmpty:   ");	

     ptrTree = TreeCreate();
    
     result = IsFullTree(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsFullTreeOnlyRoot()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsFullTreeOnlyRoot:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     
     result = IsFullTree(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsFullTreeFalseTwoNodes()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsFullTreeTrue:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 

     result = IsFullTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

/* ********************Are Similar Test**************************** */

static void AreSimilarSameTrees()
{
	int result;
	
     Tree *ptrTree , *ptrTreeTwo ;
	     
     printf("AreSimilarSameTrees:   ");	

     ptrTree = TreeCreate();
     ptrTreeTwo = TreeCreate();     
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 45);      
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);

     TreeInsert(ptrTreeTwo , 20); 
     TreeInsert(ptrTreeTwo , 10); 
     TreeInsert(ptrTreeTwo , 5); 
     TreeInsert(ptrTreeTwo , 15); 
     TreeInsert(ptrTreeTwo , 14); 
     TreeInsert(ptrTreeTwo , 19); 
     TreeInsert(ptrTreeTwo , 50);
     TreeInsert(ptrTreeTwo , 45);      
     TreeInsert(ptrTreeTwo , 60);   
     TreeInsert(ptrTreeTwo , 65);     
     TreeInsert(ptrTreeTwo , 55);
     
     result = AreSimilar(ptrTree ,ptrTreeTwo);	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
     TreeDestroy(ptrTreeTwo);     
}

static void AreSimilarDifferentTrees()
{
	int result;
	
     Tree *ptrTree , *ptrTreeTwo ;
	     
     printf("AreSimilarDifferentTrees:   ");	

     ptrTree = TreeCreate();
     ptrTreeTwo = TreeCreate();     
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 45);      
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);

     TreeInsert(ptrTreeTwo , 20); 
     TreeInsert(ptrTreeTwo , 10); 
     TreeInsert(ptrTreeTwo , 5); 
     TreeInsert(ptrTreeTwo , 15); 
     TreeInsert(ptrTreeTwo , 14); 
     TreeInsert(ptrTreeTwo , 19); 
     TreeInsert(ptrTreeTwo , 50);
     TreeInsert(ptrTreeTwo , 45);      
     TreeInsert(ptrTreeTwo , 60);   
     TreeInsert(ptrTreeTwo , 65);     

     
     result = AreSimilar(ptrTree ,ptrTreeTwo);	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
     TreeDestroy(ptrTreeTwo);
}

static void AreSimilarDifferentTreesLeft()
{
	int result;
	
     Tree *ptrTree , *ptrTreeTwo ;
	     
     printf("AreSimilarDifferentTreesLeft:   ");	

     ptrTree = TreeCreate();
     ptrTreeTwo = TreeCreate();     
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 45);      
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);

     TreeInsert(ptrTreeTwo , 20); 
     TreeInsert(ptrTreeTwo , 10); 
     TreeInsert(ptrTreeTwo , 15); 
     TreeInsert(ptrTreeTwo , 14); 
     TreeInsert(ptrTreeTwo , 19); 
     TreeInsert(ptrTreeTwo , 50);
     TreeInsert(ptrTreeTwo , 45);      
     TreeInsert(ptrTreeTwo , 60);   
     TreeInsert(ptrTreeTwo , 65);     
     TreeInsert(ptrTreeTwo , 55);
     
     result = AreSimilar(ptrTree ,ptrTreeTwo);	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
     TreeDestroy(ptrTreeTwo);
}

static void AreSimilarDifferentTreesMiddle()
{
	int result;
	
     Tree *ptrTree , *ptrTreeTwo ;
	     
     printf("AreSimilarDifferentTreesMiddle:   ");	

     ptrTree = TreeCreate();
     ptrTreeTwo = TreeCreate();     
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 45);      
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);

     TreeInsert(ptrTreeTwo , 20); 
     TreeInsert(ptrTreeTwo , 10); 
     TreeInsert(ptrTreeTwo , 5);      
     TreeInsert(ptrTreeTwo , 15); 
     TreeInsert(ptrTreeTwo , 14);  
     TreeInsert(ptrTreeTwo , 50);
     TreeInsert(ptrTreeTwo , 45);      
     TreeInsert(ptrTreeTwo , 60);   
     TreeInsert(ptrTreeTwo , 65);     
     TreeInsert(ptrTreeTwo , 55);
     
     result = AreSimilar(ptrTree ,ptrTreeTwo);	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
     TreeDestroy(ptrTreeTwo);
}

static void AreSimilarNullTrees()
{
	int result;
	
     printf("AreSimilarNullTrees:   ");	
     
     result = AreSimilar(NULL ,NULL);	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
}

static void AreSimilarEmptyTrees()
{
	int result;
	
     Tree *ptrTree , *ptrTreeTwo ;
	     
     printf("AreSimilarEmptyTrees:   ");	

     ptrTree = TreeCreate();
     ptrTreeTwo = TreeCreate();     
          
     result = AreSimilar(ptrTree ,ptrTreeTwo);	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
     TreeDestroy(ptrTreeTwo);
}

static void AreSimilarEmptyAndNullTrees()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("AreSimilarEmptyAndNullTrees:   ");	

     ptrTree = TreeCreate(); 
          
     result = AreSimilar(ptrTree ,NULL);	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void AreSimilarEmptyAndNullTrees2()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("AreSimilarEmptyAndNullTrees2:   ");	

     ptrTree = TreeCreate(); 
          
     result = AreSimilar(NULL ,ptrTree);	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void AreSimilarRootTrue()
{
	int result;
	
     Tree *ptrTree , *ptrTreeTwo ;
	     
     printf("AreSimilarRootTrue:   ");	

     ptrTree = TreeCreate();
     ptrTreeTwo = TreeCreate();     
     TreeInsert(ptrTree , 20); 

     TreeInsert(ptrTreeTwo , 20); 
     
     result = AreSimilar(ptrTree ,ptrTreeTwo);	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
     TreeDestroy(ptrTreeTwo);     
}

static void AreSimilarRootFalse()
{
	int result;
	
     Tree *ptrTree , *ptrTreeTwo ;
	     
     printf("AreSimilarRootFalse:   ");	

     ptrTree = TreeCreate();
     ptrTreeTwo = TreeCreate();     
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 22);

     TreeInsert(ptrTreeTwo , 20); 
     
     result = AreSimilar(ptrTree ,ptrTreeTwo);	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
     TreeDestroy(ptrTreeTwo);
}

/* ********************Is Perfect Tree Test**************************** */

static void IsPerfectTreeNegative()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeNegative:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 45);      
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreePositive()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreePositive:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 4); 
     TreeInsert(ptrTree , 6);           
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 40);  
     TreeInsert(ptrTree , 32); 
     TreeInsert(ptrTree , 45);                    
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeOneRightIsMissing()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeOneRightIsMissing:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 4); 
     TreeInsert(ptrTree , 6);           
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 40);  
     TreeInsert(ptrTree , 32); 
     TreeInsert(ptrTree , 45);                    
     TreeInsert(ptrTree , 60);       
     TreeInsert(ptrTree , 55);
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeOneLeftIsMissing()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeOneLeftIsMissing:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 6);           
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 40);  
     TreeInsert(ptrTree , 32); 
     TreeInsert(ptrTree , 45);                    
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeOneMiddleIsMissing()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeOneMiddleIsMissing:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 4); 
     TreeInsert(ptrTree , 6);           
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 40);  
     TreeInsert(ptrTree , 32); 
     TreeInsert(ptrTree , 45);                    
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeTwoRightIsMissing()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeTwoRightIsMissing:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 4); 
     TreeInsert(ptrTree , 6);           
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 40);  
     TreeInsert(ptrTree , 32); 
     TreeInsert(ptrTree , 45);                    
     TreeInsert(ptrTree , 60);   
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeTwoLeftIsMissing()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeTwoLeftIsMissing:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5);           
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 40);  
     TreeInsert(ptrTree , 32); 
     TreeInsert(ptrTree , 45);                    
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeTwoMiddleIsMissing()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeTwoMiddleIsMissing:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 4); 
     TreeInsert(ptrTree , 6);           
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 50);
     TreeInsert(ptrTree , 40);  
     TreeInsert(ptrTree , 32); 
     TreeInsert(ptrTree , 45);                    
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 65);     
     TreeInsert(ptrTree , 55);
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeOnlyRoot()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeOnlyRoot:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeTwoNodes()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeTwoNodes:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeTwoNodes2()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeTwoNodes2:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20);  
     TreeInsert(ptrTree , 50);
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsPerfectTreeNull()
{
	int result;
	     
     printf("IsPerfectTreeNull:   ");	
     
     result = IsPerfectTree(NULL); 	
     
     if ( result == FALSE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
}

static void IsPerfectTreeEmpty()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsPerfectTreeEmpty:   ");	

     ptrTree = TreeCreate();
     
     result = IsPerfectTree(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTNormalTrue()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsBSTNormalTrue:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50); 
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 55);
     
     result = IsBST(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTNullTree()
{
	int result;
	     
     printf("IsBSTNullTree:   ");	
     
     result = IsBST(NULL); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
}

static void IsBSTEmptyTree()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsBSTEmptyTree:   ");	

     ptrTree = TreeCreate();
     
     result = IsBST(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTOnlyRoot()
{
	int result;
	
     Tree *ptrTree ;
	     
     printf("IsBSTOnlyRoot:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     
     result = IsBST(ptrTree); 	
     
     if ( result == TRUE )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTLeftBig()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode , *_ptrTmp;
	     
     printf("IsBSTLeftBig:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 50); 
	
	_ptrNode = GetRoot(ptrTree);
     _ptrTmp = GetLeft(_ptrNode);
     
     InsertNewData(_ptrTmp ,30);

     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTRightSmall()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode , *_ptrTmp;
	     
     printf("IsBSTRightSmall:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 50); 
	
	_ptrNode = GetRoot(ptrTree);
     _ptrTmp = GetRight(_ptrNode);
     
     InsertNewData(_ptrTmp ,15);

     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTRootBig()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode ;
	     
     printf("IsBSTRootBig:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 50); 
	
	_ptrNode = GetRoot(ptrTree);
     
     InsertNewData(_ptrNode ,100);

     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTRootSmall()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode ;
	     
     printf("IsBSTRootSmall:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 50); 
	
	_ptrNode = GetRoot(ptrTree);
     
     InsertNewData(_ptrNode ,5);

     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTBigTreeLeftBig()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode ;
	     
     printf("IsBSTBigTreeLeftBig:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50); 
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 55);
 
	_ptrNode = GetRoot(ptrTree);
	_ptrNode = GetLeft(_ptrNode);
	_ptrNode = GetLeft(_ptrNode);	
     InsertNewData(_ptrNode ,70);
     
     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTBigTreeMiddleLeftBig()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode ;
	     
     printf("IsBSTBigTreeMiddleLeftBig:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50); 
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 55);
 
	_ptrNode = GetRoot(ptrTree);
	_ptrNode = GetLeft(_ptrNode);
	_ptrNode = GetRight(_ptrNode);
	_ptrNode = GetRight(_ptrNode);
			
     InsertNewData(_ptrNode ,30);
     
     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTBigTreeMiddleLeftBig2()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode ;
	     
     printf("IsBSTBigTreeMiddleLeftBig2:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50); 
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 55);
 
	_ptrNode = GetRoot(ptrTree);
	_ptrNode = GetLeft(_ptrNode);
	_ptrNode = GetRight(_ptrNode);
			
     InsertNewData(_ptrNode ,30);
     
     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTBigTreeRightSmall()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode ;
	     
     printf("IsBSTBigTreeRightSmall:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50); 
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 55);
 
	_ptrNode = GetRoot(ptrTree);
	_ptrNode = GetRight(_ptrNode);
	_ptrNode = GetRight(_ptrNode);
			
     InsertNewData(_ptrNode ,3);
     
     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}

static void IsBSTBigTreeRightSmall2()
{
	int result;
	
     Tree *ptrTree ;
     Node *_ptrNode ;
	     
     printf("IsBSTBigTreeRightSmall2:   ");	

     ptrTree = TreeCreate();
     TreeInsert(ptrTree , 20); 
     TreeInsert(ptrTree , 10); 
     TreeInsert(ptrTree , 5); 
     TreeInsert(ptrTree , 15); 
     TreeInsert(ptrTree , 14); 
     TreeInsert(ptrTree , 19); 
     TreeInsert(ptrTree , 50); 
     TreeInsert(ptrTree , 60);   
     TreeInsert(ptrTree , 45);
 
	_ptrNode = GetRoot(ptrTree);
	_ptrNode = GetRight(_ptrNode);
	_ptrNode = GetLeft(_ptrNode);
			
     InsertNewData(_ptrNode ,3);
     
     result = IsBST(ptrTree); 	
     
     if ( result == FALSE_BST )
     {
         puts(s_pass);  
     }
     else
     {
         puts(s_failed);
     }
     
     TreeDestroy(ptrTree);
}


