#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_FILENAME    "sample.log"
int main()
{
	FILE *fp;

	fp = fopen(LOG_FILENAME, "w");
	fprintf(fp, "START TIME: \n");
	fclose(fp);

	return 0;
}

