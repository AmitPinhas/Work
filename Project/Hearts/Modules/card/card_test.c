#include <stdio.h> /* printf */
#include "card.h" /* API statements */

/* ============ Local Variable ============== */
 
 /* result test positive */
static char s_pass[] = "pass";
 /* result test negitive */
static char s_failed[] = "failed";

/* =============== Tests =================== */

/* ------------Create Card------------------ */
static void PositiveTestCreateCard();

/* ------------Destroy Card------------------ */
static void PositiveDestroyCardTest();
static void DoubleFreeDestroyCardTest();

/* --------------Get Suite------------------- */
static void PositiveTestGetSuite();

/* --------------Get Rank------------------- */
static void PositiveTestGetRank();

/* -------------Get point------------------- */
static void PositiveTestGetPoint();


/* =============== main ==================== */
int main()
{
	printf("Create card tests :\n");
	PositiveTestCreateCard();
	printf("Destroy card tests :\n");
	PositiveDestroyCardTest();
	DoubleFreeDestroyCardTest();	
	printf("Get Suite tests :\n");
	PositiveTestGetSuite();
	printf("Get Rank tests :\n");
	PositiveTestGetRank();
	printf("Get point tests :\n");
	PositiveTestGetPoint();				
	return 1;
}

/* ================ Func Tests =============== */

/* ----------------Create Card---------------- */
static void PositiveTestCreateCard()
{
	Card *ptrCard ;
	
	ptrCard = CreateCard(HEART , KING);
	
	if ( NULL != ptrCard )
	{
		puts(s_pass);
	}
	else
	{
		printf(" Positive Test Creat Card : ");
		puts(s_failed);
	}
	
	DestroyCard(&ptrCard) ; 
}


/* ---------------Destroy Card------------ */
static void PositiveDestroyCardTest()
{
	Card *ptrCard ;
	
	ptrCard = CreateCard(CLUB , FOUR);
	DestroyCard(&ptrCard) ;
	if ( NULL == ptrCard )
	{
	     puts(s_pass);
	}
	else
	{
		printf(" Positiv eDestroy Card Test : ");
		puts(s_failed);
	}	
}

/* ------------------------------------------ */
static void DoubleFreeDestroyCardTest()
{
	Card *ptrCard ;
	
	ptrCard = CreateCard(SPADES , FIVE);
	DestroyCard(&ptrCard);
	DestroyCard(&ptrCard);	
	if ( NULL == ptrCard )
	{
	     puts(s_pass);
	}
	else
	{
		printf(" Double Free Destroy Card Test : ");
		puts(s_failed);
	}	
}

/* -------------Get Suite------------------- */

void PositiveTestGetSuite()
{
	Card *ptrCard ;	
	Suite varSuite;
	
	ptrCard = CreateCard( HEART ,ACE );	
	
	varSuite = GetSuite( ptrCard );
	
	if ( HEART == varSuite )
	{
		puts (s_pass);
	}
	else
	{
		printf("Positive Test Get Suite : ");
		puts (s_failed);		
	}
	
	DestroyCard(&ptrCard);
}

/* ------------------Get Rank----------------- */

void PositiveTestGetRank()
{
	Card *ptrCard ;
	Rank varRank;
	
	ptrCard = CreateCard( CLUB ,JACK );	
	
	varRank = GetRank( ptrCard );
	
	if ( (JACK == varRank) )
	{
		puts (s_pass);
	}
	else
	{
		printf("Positive Test Get Rank : ");
		puts (s_failed);		
	}
	
	DestroyCard(&ptrCard);
}

/* ------------------Get point---------------- */
static void PositiveTestGetPoint()
{
	Card *ptrCardHeart , *ptrCardSpadesQueen , *ptrRegularCard ;
	int point13 , point1 , point0 ;
	
	ptrCardHeart = CreateCard( HEART ,JACK );		
	ptrCardSpadesQueen = CreateCard( SPADES , QUEEN );
	ptrRegularCard = CreateCard( CLUB ,JACK );	
	
	point1 = GetPoint(ptrCardHeart);
	point13 = GetPoint(ptrCardSpadesQueen);
	point0 = GetPoint(ptrRegularCard);
	
	if ( (point1 == 1) && (point13 == 13) && (point0 == 0) )
	{
		puts (s_pass);
	}
	else
	{
		printf("Positive Test Get Point : ");
		puts (s_failed);		
	}
	
	DestroyCard(&ptrCardHeart);
	DestroyCard(&ptrCardSpadesQueen);
	DestroyCard(&ptrRegularCard);			
}
