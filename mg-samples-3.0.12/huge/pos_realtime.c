#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_time()
{
	time_t timep;
	time(&timep);
	printf("%s",asctime(gmtime(&timep)));
}
