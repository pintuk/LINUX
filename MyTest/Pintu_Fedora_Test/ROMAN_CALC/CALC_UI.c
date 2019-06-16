
#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define	TRUE	1
#define	FALSE	0


char RomanNumber[8] = {'I', 'V', 'X', 'L', 'C', 'D', 'M', '\0'};
char Operator[5] = {'/', '*', '+', '-', '\0'};
char **RomanTable = NULL;
char roman[50] = {0};

char display[50];
extern void UI_setResult(char *pszNumber);



/* New */
char store[20];
char result[20];
int sindex = 0;
char op = 0;


int isRoman(char c)
{
	char *p = RomanNumber;
	while(*p != '\0')
	{
		if(*p == c) return(TRUE);
		p++;
	}
	return(FALSE);
}


int isOperator(char c)
{
	char *p = Operator;
	while(*p != '\0')
	{
		if(*p == c) return(TRUE);
		p++;
	}
	return(FALSE);
}


char *IntToRoman(int num)
{
	int i = 0;
	//char roman[50];

	memset(roman,'\0',sizeof(roman));

	if(num >= 4000)
	{
		//printf("\n Value > 3000 - Over Limit!!!\n");
		num = 0;
		//exit(-1);
	}
	if(num <= 0) 
	{
		roman[i++] = 'N';
	}
	while(num >= 1000)
	{
		roman[i++] = 'M';
		num = num - 1000;
	}
	while(num >= 900)
	{
		roman[i++] = 'C';
		roman[i++] = 'M';
		num = num - 900;
	}
	while(num >= 500)
	{
		roman[i++] = 'D';
		num = num - 500;
	}
	while(num >= 400)
	{
		roman[i++] = 'C';
		roman[i++] = 'D';
		num = num - 400;
	}
	while(num >= 100)
	{
		roman[i++] = 'C';
		num = num - 100;
	}
	while(num >= 90)
	{
		roman[i++] = 'X';
		roman[i++] = 'C';
		num = num - 90;
	}
	while(num >= 50)
	{
		roman[i++] = 'L';
		num = num - 50;
	}
	while(num >= 40)
	{
		roman[i++] = 'X';
		roman[i++] = 'L';
		num = num - 40;
	}
	while(num >= 10)
	{
		roman[i++] = 'X';
		num = num - 10;
	}
	while(num >= 9)
	{
		roman[i++] = 'I';
		roman[i++] = 'X';
		num = num - 9;
	}
	while(num >= 5)
	{
		roman[i++] = 'V';
		num = num - 5;
	}
	while(num >= 4)
	{
		roman[i++] = 'I';
		roman[i++] = 'V';
		num = num - 4;
	}
	while(num >= 1)
	{
		roman[i++] = 'I';
		num = num - 1;
	}
	roman[i] = '\0';
	return(roman);
}


int RToInt(char c)
{
	int num = 0;

	switch(c)
	{
		case 'N':
			num = 0;
		break;
		case 'I':
			num = 1;
		break;
		case 'V':
			num = 5;
		break;
		case 'X':
			num = 10;
		break;
		case 'L':
			num = 50;
		break;
		case 'C':
			num = 100;
		break;
		case 'D':
			num = 500;
		break;
		case 'M':
			num = 1000;
		break;
		default:
		break;
	}
	if(num >= 4000)
	{
		//printf("\n Value > 3000 - Over Limit!!!\n");
		num = 0;
		//exit(-1);
	}
	return(num);
}

int RomanToInteger(char *data)
{
	int num = 0; int lastnum = 0; int sum = 0; int len = 0;
	int j = 0; //int flag = 0;

	/*
	for(j=0; j<=3000; j++)
	{
		if(strcmp(data,IntToRoman(j)) == 0)
		{
			flag = 1;
			break;
		}
		else
		flag = 0;
	}
	if(flag == 0)
	{
		printf("\nINVALID Roman Number <<%s>>\n\n",data);
		exit(-1);
	}
	*/
	sum = lastnum = num = 0;
	len = strlen(data);
	for(j=len-1; j >= 0; j--)
	{
		num = RToInt(data[j]);
		if(lastnum > num)
		{
			sum = sum - num; //lastnum - num;
		}
		else
		{
			sum = sum + num;
		}
		lastnum = num;
	}
	if(sum >= 4000)
	{
		//printf("\n Value > 3000 - Over Limit!!!\n");
		//exit(-1);
		sum = 0;
	}
	return(sum);
}


void CALC_onChar(char c)
{
	//char store[20] = {0};
	//char op = 0;
	int j = 0;
	int flag = 0;
	
		//if(isRoman(c))
		if(!isOperator(c) && (c != '='))
		{
			store[sindex++] = c; return;
		}

		if(isOperator(c) || (c == '='))
		{	
			store[sindex] = '\0'; sindex = 0;
			flag = 0;
		
			for(j = 0; j < 4000; j++)
			{
				if( strcmp(store,IntToRoman(j)) == 0  )
				//if( (strcmp("I",IntToRoman(j)) == 0) || (strcmp("II",IntToRoman(j)) == 0))
				{
					//printf("\n --- flag = 1-----\n");
				    //printf("\nstore = %s\n",store);
				    //printf("\nIntToRoman(%d) = %s\n",j,IntToRoman(j));
					flag = 1; break;
				}
				else
				{
					flag = 0;
				}
			}
			if(flag == 0)
			{
				memset(result,'\0',sizeof(result));
				memset(store,'\0',sizeof(store));
				result[0] = 'N'; result[1] = '\0';
				store[0] = 'N'; store[1] = '\0';
			}
			

			if(op == 0)
			{
				//result = IntToRoman(RomanToInteger(store));
				strcpy(result,store);
			}
			if(op == '+')
			{
				//result = IntToRoman(RomanToInteger(result) + RomanToInteger(store));
				strcpy(result,IntToRoman(RomanToInteger(result) + RomanToInteger(store)));
			}
			if(op == '-')
			{
				//result = IntToRoman(RomanToInteger(result) - RomanToInteger(store));
				strcpy(result,IntToRoman(RomanToInteger(result) - RomanToInteger(store)));
			}
			if(op == '*')
			{
				//result = IntToRoman(RomanToInteger(result) * RomanToInteger(store));
				strcpy(result,IntToRoman(RomanToInteger(result) * RomanToInteger(store)));
			}
			if(op == '/')
			{
				//result = IntToRoman(RomanToInteger(result) / RomanToInteger(store));
				if(RomanToInteger(store) <= 0) strcpy(result,"N");
				else
				strcpy(result,IntToRoman(RomanToInteger(result) / RomanToInteger(store)));
			}
			//if(op == '=') continue;

			switch(c)
			{
				case '+':
					op = '+';
				break;
				case '-':
					op = '-';
				break;
				case '*':
					op = '*';
				break;
				case '/':
					op = '/';
				break;
				case '=':
					op = '=';
				break;
				default:
				break;
			}
			UI_setResult(result);
		}
}

void CALC_initialize(void)
{
	memset(store,'\0',sizeof(store));
	memset(result,'\0',sizeof(result));
	sindex = 0;
	op = 0;
	result[0] = 'N'; result[1] = '\0';
	UI_setResult(result);
}

void CALC_finalize()
{
	memset(display,'\0',sizeof(display));
	strcpy(display,result);
}


#ifdef __cplusplus
}
#endif

