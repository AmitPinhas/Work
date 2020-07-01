
#include "bonus.h"

/* ********************Tree Print Test**************************** */

static void PrintTreePreOrder();
static void PrintTreeInOrder();
static void PrintTreePostOrder();
static void PrintTreeNull();
static void PrintTreeWrongTreeTravers();


/* ********************Is Full Tree Test**************************** */

static void IsFullTreeFalse();
static void IsFullTreeTrue();
static void IsFullTreeNull();
static void IsFullTreeEmpty();
static void IsFullTreeOnlyRoot();
static void IsFullTreeFalseTwoNodes();

/* ********************Are Similar Test**************************** */

static void AreSimilarSameTrees();
static void AreSimilarDifferentTrees();
static void AreSimilarDifferentTreesLeft();
static void AreSimilarDifferentTreesMiddle();
static void AreSimilarNullTrees();
static void AreSimilarEmptyTrees();
static void AreSimilarEmptyAndNullTrees();
static void AreSimilarEmptyAndNullTrees2();
static void AreSimilarRootTrue();
static void AreSimilarRootFalse();

/* ********************Is Perfect Tree Test**************************** */

static void IsPerfectTreeNegative();
static void IsPerfectTreePositive();
static void IsPerfectTreeOneRightIsMissing();
static void IsPerfectTreeOneLeftIsMissing();
static void IsPerfectTreeOneMiddleIsMissing();
static void IsPerfectTreeTwoRightIsMissing();
static void IsPerfectTreeTwoLeftIsMissing();
static void IsPerfectTreeTwoMiddleIsMissing();
static void IsPerfectTreeOnlyRoot();
static void IsPerfectTreeTwoNodes();
static void IsPerfectTreeTwoNodes2();
static void IsPerfectTreeNull();
static void IsPerfectTreeEmpty();


/* ********************Is BST Test**************************** */
static void IsBSTNormalTrue();
static void IsBSTNullTree();
static void IsBSTEmptyTree();
static void IsBSTOnlyRoot();
static void IsBSTLeftBig();
static void IsBSTRightSmall();
static void IsBSTRootBig();
static void IsBSTRootSmall();
static void IsBSTBigTreeLeftBig();
static void IsBSTBigTreeMiddleLeftBig();
static void IsBSTBigTreeMiddleLeftBig2();
static void IsBSTBigTreeRightSmall();
static void IsBSTBigTreeRightSmall2();

int main()
{

/* ********************Tree Print Test**************************** */
     
     PrintTreePreOrder();
     PrintTreeInOrder();
     PrintTreePostOrder();
     PrintTreeNull();
     PrintTreeWrongTreeTravers();
     putchar('\n');

/* ********************Is Full Tree Test**************************** */
     
     IsFullTreeFalse();
     IsFullTreeTrue();
     IsFullTreeNull();
     IsFullTreeEmpty();
     IsFullTreeOnlyRoot();
     IsFullTreeFalseTwoNodes();
     putchar('\n');
     
/* ********************Are Similar Test**************************** */     

     AreSimilarSameTrees();
     AreSimilarDifferentTrees();  
     AreSimilarDifferentTreesLeft();  
     AreSimilarDifferentTreesMiddle(); 
     AreSimilarNullTrees();
     AreSimilarEmptyTrees();
     AreSimilarEmptyAndNullTrees();
     AreSimilarEmptyAndNullTrees2();
     AreSimilarRootTrue();
     AreSimilarRootFalse();
     putchar('\n');     
     
/* ********************Is Perfect Tree Test**************************** */
     
     IsPerfectTreeNegative();
     IsPerfectTreePositive();
     IsPerfectTreeOneRightIsMissing(); 
     IsPerfectTreeOneLeftIsMissing();
     IsPerfectTreeOneMiddleIsMissing(); 
     IsPerfectTreeTwoRightIsMissing();
     IsPerfectTreeTwoLeftIsMissing(); 
     IsPerfectTreeTwoMiddleIsMissing();
     IsPerfectTreeOnlyRoot();
     IsPerfectTreeTwoNodes(); 
     IsPerfectTreeTwoNodes2();
     IsPerfectTreeNull();
     IsPerfectTreeEmpty();
     putchar('\n');   
     
/* ********************Is BST Test**************************** */
     IsBSTNormalTrue();
     IsBSTNullTree();
     IsBSTEmptyTree();
     IsBSTOnlyRoot();
     IsBSTLeftBig();
     IsBSTRightSmall();
     IsBSTRootBig();
     IsBSTRootSmall();
     IsBSTBigTreeLeftBig();
     IsBSTBigTreeMiddleLeftBig();
     IsBSTBigTreeMiddleLeftBig2(); 
     IsBSTBigTreeRightSmall(); 
     IsBSTBigTreeRightSmall2(); 
               
	return 1;
}



/* ********************Tree Print Test******************** */

static void PrintTreePreOrder()
{
     BSTree *ptrTree ;
	     
     printf("PrintTreePreOrder:   ");	

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
               
     TreePrint(ptrTree , PRE_ORDER);

     puts(s_pass);  

     TreeDestroy(ptrTree);
}

static void PrintTreeInOrder()
{
     BSTree *ptrTree ;
	     
     printf("PrintTreeInOrder:   ");	

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
     TreePrint(ptrTree , IN_ORDER);

     puts(s_pass);  

     TreeDestroy(ptrTree);
}

static void PrintTreePostOrder()
{
     BSTree *ptrTree ;
	     
     printf("PrintTreePostOrder:   ");	

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
     TreePrint(ptrTree , POST_ORDER);

     puts(s_pass);  

     TreeDestroy(ptrTree);
}

static void PrintTreeNull()
{
    printf("PrintTreeNull:   ");	
    
     TreePrint(NULL , POST_ORDER);

     puts(s_pass); 
}

static void PrintTreeWrongTreeTravers()
{
     BSTree *ptrTree ;
	     
     printf("PrintTreeWrongTreeTravers:   ");	

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
            
     TreePrint(ptrTree , 5435);

     puts(s_pass);  

     TreeDestroy(ptrTree);
}

