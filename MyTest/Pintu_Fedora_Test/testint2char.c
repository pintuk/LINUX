#include<stdio.h>


void zoom(unsigned char z)
{
	printf("z = %d\n",z);

	if(z < (unsigned char)10 || z > (unsigned char)90)
	{
		printf("ERROR : not proper z....\n");
	}
}


main()
{
	int i = 0;

	printf("Enter zoom level : ");
	scanf("%d",&i);

	zoom(i);
}


