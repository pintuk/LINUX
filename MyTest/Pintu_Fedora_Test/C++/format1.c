#include<stdio.h>

int main()
{
	int count =  0;
	float f = 66.667;
	printf("%*.*f\n",10,4,1234.34);

	printf("this %n is a test\n",&count);
	printf("count = %d\n",count);
	printf("%2.5d\n",1000);

	printf("%-10.15s\n","This is a simple test.");
	printf("%3.2f\n",f);

	printf("%f\n",f);
	printf("%10f\n",f);
	printf("%014f\n",f);
	printf("010f = %010f\n",f);
	printf("011f = %011f\n",f);
	printf("012f = %012f\n",f);
	printf("013f = %013f\n",f);


	printf("021f = %021f\n",f);
	printf("022f = %022f\n",f);
	printf("023f = %023f\n",f);
	printf("024f = %024f\n",f);
	printf("025f = %025f\n",f);
	printf("----------------------\n");
	printf("031f = %031f\n",f);
	printf("032f = %032f\n",f);
	printf("033f = %033f\n",f);
	printf("034f = %034f\n",f);
	printf("035f = %035f\n",f);
	printf("----------------------\n");
	printf("041f = %041f\n",f);
	printf("042f = %042f\n",f);
	printf("043f = %043f\n",f);
	printf("044f = %044f\n",f);
	printf("045f = %045f\n",f);
}


