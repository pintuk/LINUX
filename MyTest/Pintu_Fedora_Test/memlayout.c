#include <stdio.h>

int global_var1;
int global_var2 = 5;
static int global_static_1;
static int global_static_2 = 2;
const int const_global = 100;
volatile int volatile_global;

main()
{
	volatile int volatile_local = 99;
	int local_var1;
	int local_var2 = 1;
	const int const_local = 10;
	register int reg_variable = 0x01;
	static int local_static_var1;
	static int local_static_var2 = 1;

	printf("*********************** Address Details ***********************\n");
	printf("=================================================================\n");
	printf("Address of uninitialized_local                = %p\n",&local_var1);
	printf("Address of initialized_local                  = %p\n",&local_var2);
	printf("Address of reg_variable                       = %p\n",reg_variable);

	printf("Address of uninitialized_global               = %p\n",&global_var1);
	printf("Address of uninitialized_global_static        = %p\n",&global_static_1);
	printf("Address of uninitialized_local_static         = %p\n",&local_static_var1);
	printf("Address of initialized_local_static           = %p\n",&local_static_var2);
	printf("Address of initialized_global                 = %p\n",&global_var2);
	printf("Address of initialized_global_static          = %p\n",&global_static_2);

	printf("Address of const_local                        = %p\n",&const_local);
	printf("Address of const_global                       = %p\n",&const_global);
	
	printf("Address of volatile_global                    = %p\n",&volatile_global);
	printf("Address of volatile_local                     = %p\n",&volatile_local);
	
	printf("Address of main()                             = %p\n",main);

	printf("sizeof long double = %d\n",sizeof(long double));
}
