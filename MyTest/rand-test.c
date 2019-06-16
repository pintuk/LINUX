#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MOD_VALUE	50

int unique_number(int *arr, int x)
{
	int i;
	for (i=0; i<MOD_VALUE; i++) {
		if (x == arr[i])
			return 1;
	}
	return 0;
}

int generate_unique_random(int *arr)
{
	int n = 0;
	int i,j;

	//srand (time(NULL));
#if 1
	while (n < 1000) {
		j = rand() % MOD_VALUE;
		if (!unique_number(arr, j))
			return j;
		n++;
	}
#endif
	return 0;
}

int main()
{
	int loop = 0;
	int i,j;
	int arr[MOD_VALUE+1];
	int val = 1;

while (loop < 3) 
{
	memset(arr, -1, sizeof(MOD_VALUE+1));
	srand (time(NULL) + loop*100000);
	//arr[0] = rand() % MOD_VALUE;
	for (i=0; i<MOD_VALUE; i++) {
		j = generate_unique_random(arr);
		printf("value: %d\n", j);
	}
	printf("=================================\n");
	loop++;
	sleep(1);
}
	return 0;
}

