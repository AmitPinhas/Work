#include <stdio.h> /* printf , NULL */
#include "../include/deck.h" /* API statements */

/* ========================================================== Local Variable ================================================================== */
 
 /* result test positive */
static char s_pass[] = "pass";
 /* result test negitive */
static char s_failed[] = "failed";

/* ========================================================== Tests ============================================================================ */

/* -------------------------------------------------Create Deck------------------------------------------------------ */
static void PositiveTestCreateDeckSize52();
static void PositiveTestCreateDeckSize13();

/* -------------------------------------------------Delete Card From Deck------------------------------------------------------ */
static void PositiveTestDeleteCard();

/* -------------------------------------------------Set Card To Deck------------------------------------------------------ */
static void PositiveTestSetCard();

/* ========================================================== main ============================================================================== */
int main()
{
	printf("Create deck tests :\n");
	PositiveTestCreateDeckSize52();
	PositiveTestCreateDeckSize13();
	printf("Create deck tests :\n");
	PositiveTestDeleteCard();
	printf("Set Card To Deck tests :\n");
	PositiveTestSetCard();	
	return 1;
}

/* ====================================================== Func Tests ============================================================================ */

/* -------------------------------------------------Create Deck------------------------------------------------------ */
static void PositiveTestCreateDeckSize52()
{
	Deck *ptrDeck ;
	
	ptrDeck = CreateDeck(52);
	
	PrintDeck(ptrDeck);

	if ( NULL != ptrDeck )
	{
		puts(s_pass);
	}
	else
	{
		printf("Positive Test Create Deck Size 52: ");
		puts(s_failed);
	}
	
	DestroyDeck(&ptrDeck) ; 
}

/* ----------------------------------------------------------------------------------------------------------------- */
static void PositiveTestCreateDeckSize13()
{
	Deck *ptrDeck ;
	
	ptrDeck = CreateDeck(13);
	
	PrintDeck(ptrDeck);
	
	if ( NULL != ptrDeck )
	{
		puts(s_pass);
	}
	else
	{
		printf("Positive Test Create Deck Size 13: ");
		puts(s_failed);
	}
	
	DestroyDeck(&ptrDeck) ;
}

/* -------------------------------------------------Delete Card From Deck------------------------------------------------------ */
static void PositiveTestDeleteCard()
{
	Deck *ptrDeck ;
	Card *ptrCard ;
	
	ptrDeck = CreateDeck(52);
	
	PrintDeck(ptrDeck);
	putchar('\n');
	putchar('\n');	
	ptrCard = DeleteCardFromDeck(ptrDeck ,4);
	
	PrintDeck(ptrDeck);
		putchar('\n');
			putchar('\n');
	PrintCard(ptrCard);
		putchar('\n');
	
	if ( NULL != ptrCard )
	{
		puts(s_pass);
	}
	else
	{
		printf("Positive Test Delete Card : ");
		puts(s_failed);
	}
	
	DestroyDeck(&ptrDeck) ; 	
	DestroyCard(&ptrCard) ;
}


/* -------------------------------------------------Set Card To Deck------------------------------------------------------ */
static void PositiveTestSetCard()
{
	Deck *ptrDeck ;
	
	ptrDeck = CreateDeck(52);
	PrintDeck(ptrDeck);
	putchar('\n');
	putchar('\n');	
	putchar('\n');
     SetCardToDeck(ptrDeck ,0 , CreateCard(HEART , ACE));
	
	PrintDeck(ptrDeck);
	putchar('\n');
	putchar('\n');
	
	if ( NULL != ptrDeck )
	{
		puts(s_pass);
	}
	else
	{
		printf("Positive Test Set Card : ");
		puts(s_failed);
	}
	
	DestroyDeck(&ptrDeck) ; 
}

