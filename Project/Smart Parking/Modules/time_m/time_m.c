#include <time.h>

int Time_mGetCurrTime()
{
	return (clock()/CLOCKS_PER_SEC) ;
}
