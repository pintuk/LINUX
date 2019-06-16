
#include <stdio.h>
#include <string.h>

//using namespace std;

// prototype for function
int roman();

main(int argc, char *argv[])
{
roman();
//system("PAUSE");
//return EXIT_SUCCESS;
}

int roman()
{
     char roman_num[10];
	 printf("Enter a roman number: \n");
	 scanf("%s",roman_num);
	 int len = strlen(roman_num);
	 int number = 0;
	 int counter = 0;
	 int b4sum = 0;
	 int sum = 0;

	 for (counter = len-1; counter >= 0; counter--)
		 {
			 if (roman_num[counter] == 'M' || roman_num[counter] == 'm')
				 number = 1000;
			 else if (roman_num[counter] == 'D' || roman_num[counter] == 'd')
				 number = 500;
			 else if (roman_num[counter] == 'C' || roman_num[counter] == 'c')
				 number = 100;
			 else if (roman_num[counter] == 'L' || roman_num[counter] == 'l')
				 number = 50;
			 else if (roman_num[counter] == 'X' || roman_num[counter] == 'x')
				 number = 10;
			 else if (roman_num[counter] == 'V' || roman_num[counter] == 'v')
				 number = 5;
			 else if (roman_num[counter] == 'I' || roman_num[counter] == 'i')
				 number = 1;
			 else
				 number = 0;

			 if (b4sum > number)
				 sum = sum - number;//b4sum - number;
			 else
			 {
				 sum = sum + number;
			 }
			 	b4sum = number;
		}

	printf("Integer = %d\n",sum );
}
