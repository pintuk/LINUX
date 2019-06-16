#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NUM		36

#define SWAP(a,b)	do { \
				int t; \
				t = a; \
				a = b; \
				b = t; \
			} while (0)

int generate_random_array(int *arr)
{
	int i,j;
	int visited[MAX_NUM+1] = {0,};
	static int random = 3;

	//random = arr[MAX_NUM/2];
	printf("random value: %d\n", random);
	//srand(time(NULL) + random*MAX_NUM);
	//srand(random*time(NULL));
	srand(random);
	random = rand() % MAX_NUM;
	j=1;
	for (i=0; i<MAX_NUM; i++) {
		int a,b;
		a = arr[i];
		b = arr[(i + j*random)%MAX_NUM];
		//if (visited[a] || visited[b]) continue;
		if (visited[a]) continue;
		if (visited[b]) { 
			j++;
			continue;
		}
		SWAP(arr[a], arr[b]);
		visited[a] = visited[b] = 1;
		j++;
	}
}

int main()
{
	int i,j;
	int arr[MAX_NUM+1] = {0,};
	int loop = 0;
	long int value = 0;

	value = time(NULL);
	printf("time value: %ld\n", value);

	for (i=0; i<MAX_NUM; i++) {
		arr[i] = i;
		printf("value: %d\n", arr[i]);
	}
	printf("===================\n");
	while (loop < 10) {
		//srand(value);
		//random = rand() % MAX_NUM;
		generate_random_array(arr);
		for (i=0; i<MAX_NUM; i++) {
			printf("value: %d\n", arr[i]);
		}
		printf("===================\n");
		loop++;
		//random += 3;
	}
	return 0;
}
