#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct
{
	unsigned int vals3;
	unsigned char bit3;
}S3;

typedef struct
{
	unsigned int vals2;
	unsigned char bit2;
}S2;

typedef struct 
{
	unsigned int vals1;
	unsigned char bit1;
	S2 s2;
	S3 s3;
}S1;


main()
{
	S1 s1; S1 *ptrs1 = NULL;
	
	printf("size of S1 = %d\n",sizeof(S1));
	ptrs1 = (S1 *)malloc(sizeof(S1));

	memset(ptrs1, 0, sizeof(S1));
	memset(&s1, 0, sizeof(S1));
	if(ptrs1 == NULL)
	{
		printf("Error : memory not allocated....\n");
		exit(0);
	}
	printf("Memory allocated for S1....\n");
	printf("s1.s3.vals3 = %d\n",s1.s3.vals3);
	printf("ptrs1->s3.vals3 = %d\n",ptrs1->s3.vals3);
	free(ptrs1);
	ptrs1 = NULL;
}

