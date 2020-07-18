#include <stdio.h> /* printf , NULL */
#include "round.h" 

/* ============= Local Variable ============= */
 
 /* result test positive */
static char s_pass[] = "pass";
 /* result test negitive */
static char s_failed[] = "failed";

/* ================= Tests ================== */

/* -------------- Create round -------------- */
static void PositiveTestCreateRound();

/* -------------- Destroy round ------------- */
static void DoubleFreeDestroyRoundTest();


/* ================= main =================== */
int main()
{
	printf("Create round tests :\n");
	PositiveTestCreateRound();
	printf("Destroy round tests :\n");
	DoubleFreeDestroyRoundTest();
	return 1;
}

/* ================ Func Tests ============= */

/* -------------- Create round ------------- */
static void PositiveTestCreateRound()
{
	Round *ptrRound ;
	
	ptrRound = CreateRound();
	
	if (  ptrRound != NULL )
	{
		puts(s_pass);
	}
	else
	{
		printf("Positive Test Create Round : ");
		puts(s_failed);
	}
	
	DestroyRound(&ptrRound);		
}

/* ------------- Destroy round -------------- */
static void DoubleFreeDestroyRoundTest()
{
	Round *ptrRound ;
	
	ptrRound = CreateRound();

	DestroyRound(&ptrRound);	
	DestroyRound(&ptrRound);
	puts(s_pass);		
}
