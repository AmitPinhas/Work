#include "../include/log.h"

#define LOG_FILE "log.txt"

int main()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	LOG( "test3" , OK );
#pragma GCC diagnostic pop
	return 0;
}

