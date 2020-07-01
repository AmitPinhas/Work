#include <stdio.h> /* printf , NULL */
#include "../include/player.h" /* API statements */

/* ========================================================== Local Variable ================================================================== */
 
 /* result test positive */
static char s_pass[] = "pass";
 /* result test negitive */
static char s_failed[] = "failed";

/* ========================================================== Tests ============================================================================ */

/* -------------------------------------------------Create player------------------------------------------------------ */
static void PositiveTestCreateplayer();

/* -------------------------------------------------Destroy player----------------------------------------------------- */
static void DoubleFreeDestroyplayerTest();

/* ------------------------------------------------------ Set and Get Points ------------------------------------------- */
static void PositiveSetAndGetPoints();
/* ------------------------------------------------------ Set Deck ----------------------------------------------------- */
static void PositiveSetDeck();


/* ========================================================== main ============================================================================ */

int main()
{
	printf("Create player tests :\n");
	PositiveTestCreateplayer();
	printf("Destroy player tests :\n");
	DoubleFreeDestroyplayerTest();
	printf("Set and Get Points tests :\n");	
	PositiveSetAndGetPoints();
	printf("Set Deck tests :\n");	
	PositiveSetDeck();
	return 1;
}


/* ====================================================== Func Tests ============================================================================ */

/* -------------------------------------------------Create player------------------------------------------------------ */
static void PositiveTestCreateplayer()
{
	Player *ptrNewPlayer = CreatePlayer("Avi" , COMPUTER );
	
	if ( ptrNewPlayer != NULL )
	{
		puts(s_pass);
	}
	else
	{
		printf("Positive Test Create player : ");
		puts(s_failed);
	}
	
	DestroyPlayer(&ptrNewPlayer);
}


/* -------------------------------------------------Destroy player------------------------------------------------------ */
static void DoubleFreeDestroyplayerTest()
{
	Player *ptrNewPlayer = CreatePlayer("Avi" , COMPUTER );

	DestroyPlayer(&ptrNewPlayer);
	DestroyPlayer(&ptrNewPlayer);
	puts(s_pass);
}

/* ------------------------------------------------------ Set and Get Points -------------------------------------------------- */
static void PositiveSetAndGetPoints()
{
	Player *ptrNewPlayer = CreatePlayer("Avi" , COMPUTER );
	int points;
	
	SetPoints(ptrNewPlayer , 50) ;
	
	points = GetPoints(ptrNewPlayer) ;
	
	if ( 50 == points )
	{
		puts(s_pass);
	}
	else
	{
		printf("Positive Set Ang Get Points : ");
		puts(s_failed);
	}	
	
	DestroyPlayer(&ptrNewPlayer);		
}

/* ------------------------------------------------------ Set Deck ----------------------------------------------------- */
static void PositiveSetDeck()
{
	Player *ptrNewPlayer = CreatePlayer("Avi" , COMPUTER );	
	Deck *ptrDeck = CreateDeck(13);
	Deck *prtDeckPlayer ;
	int index , index2=0 ;
	Card *_card;
	
	for ( index = 12 ; index >= 0 ; index-- , index2++ )
	{
		_card = CreateCard( index/4 , index ) ;
		SetCardToDeck(ptrDeck , index2 , _card);
	}
	PrintDeck(ptrDeck);
	putchar('\n');
	SetDeck(ptrNewPlayer ,ptrDeck);

	prtDeckPlayer = GetDeck(ptrNewPlayer);
	
	PrintDeck(prtDeckPlayer);
	putchar('\n');	
	if ( NULL != prtDeckPlayer )
	{
		puts(s_pass);
	}
	else
	{
		printf("Positive Set Deck : ");
		puts(s_failed);
	}
	DestroyDeck(&ptrDeck);
	DestroyPlayer(&ptrNewPlayer);	
}

