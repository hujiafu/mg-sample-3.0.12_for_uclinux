#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_time()
{
	time_t timep;
	struct tm *p;

	time(&timep);
	p=localtime(&timep);
	printf ("%d%d%d", (1900+p->tm_year),(1 + p->tm_mon), p->tm_mday);
	printf("%d:%d:%d\n",p->tm_hour, p->tm_min, p->tm_sec);
}


