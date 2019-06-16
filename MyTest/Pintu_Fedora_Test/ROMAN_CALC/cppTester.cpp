#include <stdio.h>
#include <string.h>

//#include "CALC.h"

#include "romancalc.h"

void sendToCalc(const char* buf)
{
	for(char* ptr = (char*)buf; *ptr; ptr ++)
	{
		CALC_onChar(*ptr);
	}
}

bool first = true;
char result[3000];

void UI_resetResult()
{
	first = true;
	result[0] = 0;
}

void UI_setResult(const char* pszNumber)
{
	if ( first == false )
	{
		strcat(result, ",");
	}
	else
	{
		first = false;
	}

	strcat(result, pszNumber);
}

int main(int argc, char* argv[])
{
	if ( argc < 2 )
	{
		printf("Usage: %s <test.dat>\n", argv[0]);
		return -2;
	}

	FILE *fp;
	if ( (fp = fopen(argv[1], "rt")) == NULL )
	{
		printf("Usage: %s <test.dat>\n", argv[0]);
		return -1;
	}

	char input[3000], output[3000];

	int tc = 0, passed = 0;
	while(!feof(fp))
	{
		if (fgets(input, 3000, fp) == NULL) break;
		if (fgets(output, 3000, fp) == NULL) break;

		input[strlen(input) - 1] = 0;
		output[strlen(output) - 1] = 0;
		printf("Input = %s\n\n",input);
		printf("Output = %s\n\n",output);
		UI_resetResult();

		tc ++;

		CALC_initialize();
		sendToCalc(input);
		CALC_finalize();

		if ( strcmp(output, result) == 0 )
		{
			printf("TC%d: PASSED\n", tc);
			passed ++;
		}
		else
		{
			printf("TC%d: FAILED\n", tc);
		}
	}

	fclose(fp);

	printf("Test Result: %d passed, %d failed in %d test cases\n",
		passed, tc - passed, tc);

	return 0;
}

