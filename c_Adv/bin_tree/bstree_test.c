#include <stdio.h>  /* null , printf */
#include "bstree.h" /* api statements */


/* --------------------------------------- local variables ---------------------------- */
static char s_pass[]="pass";
static char s_failed[]="failed";


/* ------------------------------------------ print func ------------------------------- */
void InOrder(BSTree *_tree);

/* ---------------------------------------- comparator func ---------------------------- */
int LessComparator2(void* _left, void* _right)
{
     return (*(int*)_left) < (*(int*)_right) ;
}

/* ------------------------------------------ fault itr --------------------------------- */
int IsFaultItr(BSTreeItr _it);

/* =========================================================== tests ============================================================================== */

/* ---------------------- BSTree Create Test ---------------------- */

static void PositiveTreeCreate();
static void NullFuncCreate();

/* ------------------------ BSTree Destroy ------------------------ */

static void PositiveTreeDestroyManyNodes();
static void NullTreeDestroy();
static void DoubleFreeTreeDestroy();
static void DestroyWithoutNodes();

/* ------------------------ BSTree Insert ------------------------- */

static void PositivInsertManyNodes();
static void PositivInsertOneNode();
static void PositivInsertSmallNode();
static void PositivInsertBigNode();
static void NegativeInsertNull();
static void InsertSameNode();
static void InsertManyNodesWithSameNode();
static void InsertNullItem();

/* ---------------------- BSTree Itr Begin ------------------------- */
static void NullTreeBegin();
static void PositiveBegin();

/* ---------------------- BSTree Itr End ------------------------- */
static void PositiveEnd();

/* --------------------- BSTreeItrEquals ------------------------------ */
static void PositiveEquals();

/* --------------------- BSTreeItrGet -------------------------------- */
static void EmptyTreeGet();
static void PositiveGet();


/* --------------------- BSTreeItrNext -------------------------------- */
static void PositiveNext();

/* --------------------- BSTreeItrPrev -------------------------------- */
static void PositivePrev();

/* ============================================================== main ============================================================================ */

int main()
{
	printf("-----------------------------------------\n");
	printf("BSTree Create:\n\n");
     PositiveTreeCreate();  
     NullFuncCreate();

	printf("-----------------------------------------\n");	
	printf("BSTree Destroy:\n\n");	
     PositiveTreeDestroyManyNodes();
     NullTreeDestroy();  
     DoubleFreeTreeDestroy();
     DestroyWithoutNodes();

	printf("-----------------------------------------\n");	
	printf("BSTree Insert:\n\n");
     PositivInsertManyNodes();
     PositivInsertOneNode();
     PositivInsertSmallNode();
     PositivInsertBigNode();
     NegativeInsertNull();
     InsertSameNode();
     InsertManyNodesWithSameNode();
     InsertNullItem();
     
	printf("-----------------------------------------\n");	
	printf("BSTree Itr Begin:\n\n");
	NullTreeBegin();
     PositiveBegin();

	printf("-----------------------------------------\n");	
	printf("BSTree Itr End:\n\n");
	PositiveEnd();

	printf("-----------------------------------------\n");	
	printf("BSTree Itr Equals:\n\n");
	PositiveEquals();

	printf("-----------------------------------------\n");	
	printf("BSTree Itr Get:\n\n");
     EmptyTreeGet();
     PositiveGet();

	printf("-----------------------------------------\n");	
	printf("BSTree Itr Next:\n\n");
	PositiveNext();

	printf("-----------------------------------------\n");	
	printf("BSTree Itr Prev:\n\n");
     PositivePrev();
     		
     return 1;
}


/* ====================================================== func tests ============================================================================== */

/* ---------------------- BSTree Create Test ---------------------- */

static void PositiveTreeCreate()
{
     BSTree *ptrTree ;
     
     ptrTree = BSTreeCreate(LessComparator2);
     
     if ( NULL != ptrTree )
     {
          puts(s_pass);
     }
     else
     {
          printf("PositiveTreeCreate:   ");
          puts(s_failed);
     }
     
     BSTreeDestroy(ptrTree , NULL );
}

static void NullFuncCreate()
{
     BSTree *ptrTree ;
     
     ptrTree = BSTreeCreate(NULL);
     
     if ( NULL == ptrTree )
     {
          puts(s_pass);
     }
     else
     {
          printf("NullFuncCreate:   ");
          puts(s_failed);
          BSTreeDestroy(ptrTree , NULL );
     }
}

/* ------------------------ BSTree Destroy ------------------------ */

static void PositiveTreeDestroyManyNodes()
{
     BSTree *ptrTree ;
     int num1 =1 , num2 = 2 , num3 = 3 , num4 = 4 , num5=5 , num6=6 ; 
        
     ptrTree = BSTreeCreate(LessComparator2);
 
	BSTreeInsert(ptrTree , &num1);
	BSTreeInsert(ptrTree , &num2);
	BSTreeInsert(ptrTree , &num3);
	BSTreeInsert(ptrTree , &num4);
	BSTreeInsert(ptrTree , &num5);
	BSTreeInsert(ptrTree , &num6);

     BSTreeDestroy(ptrTree , NULL);   
     
     puts(s_pass);
}

static void NullTreeDestroy()
{
    BSTreeDestroy(NULL , NULL);  
    
    puts(s_pass);
}

static void DoubleFreeTreeDestroy()
{
     BSTree *ptrTree ;  
        
     ptrTree = BSTreeCreate(LessComparator2);
     
     BSTreeDestroy(ptrTree , NULL);  
     BSTreeDestroy(ptrTree , NULL);  
     
     puts(s_pass);  
}


static void DestroyWithoutNodes()
{
     BSTree *ptrTree ; 
        
     ptrTree = BSTreeCreate(LessComparator2);

     BSTreeDestroy(ptrTree , NULL);   
     
     puts(s_pass);
}
/* ------------------------ BSTree Insert ------------------------- */

static void PositivInsertManyNodes()
{
     BSTree *ptrTree ;
     BSTreeItr ptrTemp ;
     int *data;
     int num20 = 20 , num10 =10 , num5 =5 , num15=15 , num14=14 , num19=19 , num50=50 , num60 =60 , num55=55 ;

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num20); 
     BSTreeInsert(ptrTree , &num10); 
     BSTreeInsert(ptrTree , &num5); 
     BSTreeInsert(ptrTree , &num15); 
     BSTreeInsert(ptrTree , &num14); 
     BSTreeInsert(ptrTree , &num19); 
     BSTreeInsert(ptrTree , &num50); 
     BSTreeInsert(ptrTree , &num60);   
     BSTreeInsert(ptrTree , &num55);           
     ptrTemp = BSTreeItrBegin(ptrTree);
	data = BSTreeItrGet(ptrTemp);

     if( *data == 5)
     {
        puts(s_pass);  
     }
     else
     {
        printf("PositivInsertManyNodes:   ");	
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL);
}

static void PositivInsertOneNode()
{
     BSTree *ptrTree ;
     BSTreeItr ptrNode ;
     int *data;
     int num5 =5 ;	

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num5);     
     ptrNode = BSTreeItrBegin(ptrTree);
     data = BSTreeItrGet(ptrNode);

     if( *data == 5)
     {
        puts(s_pass);  
     }
     else
     { 	     
        printf("PositivInsertOneNode:   ");
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL);  
}

static void PositivInsertSmallNode()
{
     BSTree *ptrTree ;
     BSTreeItr ptrNode  ;
     int *data;
     int num5 = 5 , num3 =3 ;
     
     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num5);
     BSTreeInsert(ptrTree , &num3);     
     ptrNode = BSTreeItrBegin(ptrTree);
     data = BSTreeItrGet(ptrNode);

     if( *data == 3)
     {
        puts(s_pass);  
     }
     else
     {
        printf("PositivInsertSmallNode:   ");     
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL); 
}

static void PositivInsertBigNode()
{
     BSTree *ptrTree ;
     BSTreeItr ptrNode  ;
     int *data;
     int num5 = 5 , num6 = 6 ;
     
     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num5);
     BSTreeInsert(ptrTree , &num6);     
     ptrNode = BSTreeItrBegin(ptrTree);
     data = BSTreeItrGet(ptrNode);

     if( *data == 5)
     {
        puts(s_pass);  
     }
     else
     {
        printf("PositivInsertBigNode:   ");     
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL); 
}

static void NegativeInsertNull()
{
	int num5 = 5;
     
     if( (BSTreeInsert(NULL , &num5)) == NULL)
     {
        puts(s_pass);  
     }
     else
     {
        printf("NegativeInsertNull:   ");     
        puts(s_failed);        
     }
}

static void InsertSameNode()
{
     BSTree *ptrTree ;
     int num5 =5 ;	

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num5);     
     BSTreeInsert(ptrTree , &num5);   
     
   /*  InOrder(ptrTree); */
     
     puts(s_pass);  

     BSTreeDestroy(ptrTree , NULL);
}

static void InsertManyNodesWithSameNode()
{
     BSTree *ptrTree ;
     int num20 = 20 , num10 =10 , num5 =5 , num15=15 , num14=14 , num19=19 , num50=50 , num60 =60 , num55=55 ;

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num20); 
     BSTreeInsert(ptrTree , &num10); 
     BSTreeInsert(ptrTree , &num5); 
     BSTreeInsert(ptrTree , &num15); 
     BSTreeInsert(ptrTree , &num14); 
     BSTreeInsert(ptrTree , &num14);     
     BSTreeInsert(ptrTree , &num19); 
     BSTreeInsert(ptrTree , &num50); 
     BSTreeInsert(ptrTree , &num60);   
     BSTreeInsert(ptrTree , &num55);           

    /* InOrder(ptrTree); */

     puts(s_pass);   
     
     BSTreeDestroy(ptrTree , NULL);
}

static void InsertNullItem()
{
     BSTree *ptrTree ;
     ptrTree = BSTreeCreate(LessComparator2);
     if ( BSTreeInsert(ptrTree , NULL) == NULL )
     {
        puts(s_pass);  
     }
     else
     {
        printf("Insert Null Item:   ");     
        puts(s_failed);        
     } 
     BSTreeDestroy(ptrTree , NULL);            
}

/* ---------------------- BSTree Itr Begin ------------------------- */

static void NullTreeBegin()
{
	BSTreeItr itr;
	
	itr = BSTreeItrBegin(NULL);
	
	if (IsFaultItr(itr))
     {
        puts(s_pass);  
     }
     else
     {
        printf("Null Tree Begin:   ");     
        puts(s_failed);        
     } 
}

static void PositiveBegin()
{
     BSTree *ptrTree ;
     BSTreeItr ptrTemp ;
     int *data;
     int num20 = 20 , num10 =10 , num5 =5 , num15=15 , num14=14 , num19=19 , num50=50 , num60 =60 , num55=55 ;

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num20); 
     BSTreeInsert(ptrTree , &num10); 
     BSTreeInsert(ptrTree , &num5); 
     BSTreeInsert(ptrTree , &num15); 
     BSTreeInsert(ptrTree , &num14); 
     BSTreeInsert(ptrTree , &num19); 
     BSTreeInsert(ptrTree , &num50); 
     BSTreeInsert(ptrTree , &num60);   
     BSTreeInsert(ptrTree , &num55);           
     ptrTemp = BSTreeItrBegin(ptrTree);
	data = BSTreeItrGet(ptrTemp);

     if( *data == 5)
     {
        puts(s_pass);  
     }
     else
     {
        printf("PositivInsertManyNodes:   ");	
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL);
}


/* ---------------------- BSTree Itr End ------------------------- */
static void PositiveEnd()
{
     BSTree *ptrTree ;
     BSTreeItr ptrTemp ;
     int *data;
     int num20 = 20 , num10 =10 , num5 =5 , num15=15 , num14=14 , num19=19 , num50=50 , num60 =60 , num55=55 ;

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num20); 
     BSTreeInsert(ptrTree , &num10); 
     BSTreeInsert(ptrTree , &num5); 
     BSTreeInsert(ptrTree , &num15); 
     BSTreeInsert(ptrTree , &num14); 
     BSTreeInsert(ptrTree , &num19); 
     BSTreeInsert(ptrTree , &num50); 
     BSTreeInsert(ptrTree , &num60);   
     BSTreeInsert(ptrTree , &num55);           
     ptrTemp = BSTreeItrEnd(ptrTree);
	data = BSTreeItrGet(ptrTemp);

     if( *data == 60)
     {
        puts(s_pass);  
     }
     else
     {
        printf("Positive End:   ");	
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL);
}


/* --------------------- BSTreeItrEquals ------------------------------ */
static void PositiveEquals()
{
     BSTree *ptrTree ;
     BSTreeItr ptrNode , ptrNode2 ;
     int num5 =5 ;	

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num5);     
     ptrNode = BSTreeItrBegin(ptrTree);
     ptrNode2 = BSTreeItrEnd(ptrTree);

     if( BSTreeItrEquals(ptrNode , ptrNode2) )
     {
        puts(s_pass);  
     }
     else
     { 	     
        printf("PositiveEquals:   ");
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL); 
}


/* --------------------- BSTreeItrGet -------------------------------- */
static void EmptyTreeGet()
{
     BSTree *ptrTree ;
     BSTreeItr ptrNode;
     ptrTree = BSTreeCreate(LessComparator2);
     
     ptrNode = BSTreeItrEnd(ptrTree);
     
     if ( BSTreeItrGet(ptrNode) == NULL )
     {
        puts(s_pass);  
     }
     else
     { 	     
        printf("EmptyTree:   ");
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL);      
}


static void PositiveGet()
{
     BSTree *ptrTree ;
     BSTreeItr ptrNode ;
     int num5 =5 , *data ;	

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num5);     
     ptrNode = BSTreeItrBegin(ptrTree);
     data = BSTreeItrGet(ptrNode);

     if( *data == 5 )
     {
        puts(s_pass);  
     }
     else
     { 	     
        printf("PositiveGet:   ");
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL); 
}



/* --------------------- BSTreeItrNext -------------------------------- */
static void PositiveNext()
{
     BSTree *ptrTree ;
     BSTreeItr ptrTemp ;
     int *data;
     int num20 = 20 , num10 =10 , num5 =5 , num15=15 , num14=14 , num19=19 , num50=50 , num60 =60 , num55=55 ;

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num20); 
     BSTreeInsert(ptrTree , &num10); 
     BSTreeInsert(ptrTree , &num5); 
     BSTreeInsert(ptrTree , &num15); 
     BSTreeInsert(ptrTree , &num14); 
     BSTreeInsert(ptrTree , &num19); 
     BSTreeInsert(ptrTree , &num50); 
     BSTreeInsert(ptrTree , &num60);   
     BSTreeInsert(ptrTree , &num55);           
     ptrTemp = BSTreeItrBegin(ptrTree);
     ptrTemp = BSTreeItrNext(ptrTemp);
     ptrTemp = BSTreeItrNext(ptrTemp);
     ptrTemp = BSTreeItrNext(ptrTemp);
               
	data = BSTreeItrGet(ptrTemp);

     if( *data == 15)
     {
        puts(s_pass);  
     }
     else
     {
        printf("PositiveNext:   ");	
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL);
}


/* --------------------- BSTreeItrPrev -------------------------------- */
static void PositivePrev()
{
     BSTree *ptrTree ;
     BSTreeItr ptrTemp ;
     int *data;
     int num20 = 20 , num10 =10 , num5 =5 , num15=15 , num14=14 , num19=19 , num50=50 , num60 =60 , num55=55 ;

     ptrTree = BSTreeCreate(LessComparator2);
     BSTreeInsert(ptrTree , &num20); 
     BSTreeInsert(ptrTree , &num10); 
     BSTreeInsert(ptrTree , &num5); 
     BSTreeInsert(ptrTree , &num15); 
     BSTreeInsert(ptrTree , &num14); 
     BSTreeInsert(ptrTree , &num19); 
     BSTreeInsert(ptrTree , &num50); 
     BSTreeInsert(ptrTree , &num60);   
     BSTreeInsert(ptrTree , &num55);           
     ptrTemp = BSTreeItrEnd(ptrTree);
     ptrTemp = BSTreeItrPrev(ptrTemp);
     ptrTemp = BSTreeItrPrev(ptrTemp);
     ptrTemp = BSTreeItrPrev(ptrTemp);
               
	data = BSTreeItrGet(ptrTemp);

     if( *data == 20)
     {
        puts(s_pass);  
     }
     else
     {
        printf("PositivePrev:   ");	
        puts(s_failed); 
     }
     BSTreeDestroy(ptrTree , NULL);
}


