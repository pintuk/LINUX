#include <stdio.h>


//int (*sum_two_int) (int a, int b) ;
//void  (*set_value) (int *a, int *b);

int sum(int a, int b)
{
	printf("Sum of the numbers = %d\n", a+b);
	return a+b ;
}

void set_my_values(int *a, int *b)
{
	*a = 5;
	*b = 6;
}

void test_sum(int (*ptr2Func) (int a, int b))
{
	int c, d;
	int result = ptr2Func(3, 4);
	printf(" Result of Summation : %d \n", result);
}
void test_set_value(void (*ptr2Func) (int *a, int *b))
{
	int c = 3;
	int d = 4;
	ptr2Func(&c, &d);
	printf(" Result of Set_my_values : c= %d, d = %d \n", c, d);
}


int  main()
{
	int value ;
	int *ptr = NULL;
	ptr = (int *)sum;
	//test_sum(****sum); // WHY COMPILER IS NOT THROWING ERROR ????
	printf("sum = %p\n",sum);
	printf("*sum = %p\n",*sum);
	printf("**sum = %p\n",**sum);
	printf("***sum = %p\n",***sum);
	printf("****sum = %p\n",****sum);
	*ptr = 0x8048384;
	//test_sum( *(*(*(*(sum)))) );
	//test_sum((int (*)(int, int))ptr);
	test_sum(*ptr);
	test_set_value(set_my_values) ;
	return -1;	
}

