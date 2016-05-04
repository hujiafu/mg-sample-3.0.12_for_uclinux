#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char gtime[30];

int get_time()
{
	time_t timep;
	struct tm *p;

	time(&timep);
	p=localtime(&timep);
	sprintf (gtime, "%d-%d-%d %d:%d:%d", (1900+p->tm_year),(1 + p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	return 0;
}


