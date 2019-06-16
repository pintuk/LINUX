#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


int main()
{
	char cmdline[128];
	time_t t;
	struct tm *tmt;

	t = time(NULL);
	tmt = localtime(&t);
	strftime(cmdline, sizeof(cmdline), "%a %d/%b/%Y %T", tmt);
	printf("START TIME: %s\n", cmdline);

	return 0;
}

