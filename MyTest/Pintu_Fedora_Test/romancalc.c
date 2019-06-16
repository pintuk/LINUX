#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>



#define TRUE		1
#define FALSE		0
#define STACK_SIZE	100
#define MAX_SIZE	100


char Operator[5] = {'/', '*', '+', '-', '\0'};
char Roman[8] = {'I', 'V', 'X', 'L', 'C', 'D', 'M', '\0'};
char stack[STACK_SIZE];
int istack[STACK_SIZE];
int stack_top = -1;




int isRoman(char c)
{
	char *p = Roman;
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
	char roman[50];

	memset(roman,'\0',sizeof(roman));

	if(num > 3000)
	{
		printf("\n Value > 3000 - Over Limit!!!\n");
		exit(-1);
	}
	if(num == 0) 
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

int RomanToInt(char c)
{
	int num = 0;

	switch(c)
	{
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
	if(num > 3000)
	{
		printf("\n Value > 3000 - Over Limit!!!\n");
		exit(-1);
	}
	return(num);
}


int checkOp(char c)
{
	char *p = Operator;
	while(*p != '\0')
	{
		if(*p == c) return(TRUE);
		p++;
	}
	return(FALSE);
}

int OpPrecedence(char op)
{
	int order = -1;

	switch(op)
	{
		case '(':
			order = 0;
		break;
		case '+':
		case '-':
			order = 1;
		break;
		case '/':
		case '*':
			order = 2;
		break;
		default:
		break;
	}
	return(order);
}


int iStackIsEmpty()
{
	int *ptr = istack;

	if(ptr == NULL ) return(TRUE);

	return(FALSE);
}

int iPopFromStack()
{
	int op = 0;

	if(!iStackIsEmpty())
	{
		op = istack[stack_top];
		istack[stack_top] = '\0';
		stack_top--;
	}
	return(op);
}

void iPushToStack(int op)
{
	if(iStackIsEmpty()) 
	{
		stack_top = -1;
		memset(istack, '\0', sizeof(istack));
	}
	//stack_top = stack_index;
	istack[++stack_top] = op;
}


int StackIsEmpty()
{
	char *ptr = stack;

	if(ptr == NULL || stack[0] == '\0') return(TRUE);

	return(FALSE);
}

char PopFromStack()
{
	char op = '\0';

	if(!StackIsEmpty())
	{
		op = stack[stack_top];
		stack[stack_top] = '\0';
		stack_top--;
	}
	return(op);
}

void PushToStack(char op)
{
	if(StackIsEmpty()) 
	{
		stack_top = -1;
		memset(stack, '\0', sizeof(stack));
	}
	//stack_top = stack_index;
	stack[++stack_top] = op;
}

int Evaluate(char *postfix)
{
	char c = '\0';
	int result = 0; int i = 0; int j = 0; int x = 0; int y = 0;
	char *data = NULL;

	memset(istack,'\0',sizeof(istack));
	data = malloc(sizeof(postfix));
	for(i=0; postfix[i] != '\0'; i++)
	{
		c = postfix[i];
		if(isdigit(c))
		{
			sprintf(data,"%c",c);
			iPushToStack(atoi(data));
		}
		if(isRoman(c))
		{
			iPushToStack(RomanToInt(c));
		}
		if(checkOp(c))
		{
			x = iPopFromStack();
			y = iPopFromStack();
			switch(c)
			{
				case '+':
					iPushToStack((y+x));
				break;
				case '-':
					iPushToStack((y-x));
				break;
				case '*':
					iPushToStack((y*x));
				break;
				case '/':
					iPushToStack((y/x));
				break;
				default:
				break;
			}
		}
		if(c == '[')
		{
			int sum = 0; int lastnum = 0; int num = 0; int len = 0; int flag = 0;

			i++; j = 0;
			memset(data,'\0',sizeof(postfix));
			while(postfix[i] != ']')
			{
				data[j++] = postfix[i++];
			}
			data[j] = '\0';
			//printf("data = %s\n",data);
			flag = 0;
			for(j=0; j<=3000; j++)
			{
				if(strcmp(data,IntToRoman(j)) == 0)
				{
					flag = 1;
					break;
				}
				else
				{
					flag = 0;
				}
			}
			if(flag == 0)
			{
				printf("INVALID --- Roman Number!!!\n");
				exit(-1);
			}
			sum = lastnum = num = 0;
			len = strlen(data);
			for(j=len; j >= 0; j--)
			{
				num = RomanToInt(data[j]);
				if(lastnum > num)
				{
					sum = lastnum - num;
				}
				else
				{
					sum = sum + num;
				}
				lastnum = num;
			}
			//printf("sum = %d\n",sum);
			iPushToStack(sum);
		}
	} /* end for */
	result = iPopFromStack();
	return(result);
}

void ConvertToPostfix(char *infix, char *postfix)
{
	int i = 0; int j = 0; int k = 0;
	char c = '\0';

	memset(stack, '\0', sizeof(stack));
	for(i=0; infix[i]!= '\0'; i++)
	{
		if(isdigit(infix[i]) || isRoman(infix[i]))
		{
			postfix[j++] = infix[i];
		}
		if(infix[i] == '[' || infix[i] == ']')
		{
			postfix[j++] = infix[i];
		}
		else if(checkOp(infix[i]))
		{
			if(StackIsEmpty()) 
			{
				PushToStack(infix[i]);
				continue;
			}
			//if(!StackIsEmpty() && (stack[stack_top] == '('))
			//{
			//	PushToStack(infix[i]);
			//	continue;
			//}
			while(!StackIsEmpty())
			{
				if (OpPrecedence(stack[stack_top]) >= OpPrecedence(infix[i]))
				{
					postfix[j++] = PopFromStack();
				}
				else
				{
					//PushToStack(infix[i]);
					break;
				}
			}
			PushToStack(infix[i]);
		}
		else if(infix[i] == '(')
		{
			PushToStack(infix[i]);
		}
		else if(infix[i] == ')')
		{
			while( (c = PopFromStack()) != '(')
			{
				postfix[j++] = c;
			}
		}
	}
	while(!StackIsEmpty())
	{
		postfix[j++] = PopFromStack();
	}
	postfix[j] = '\0';
}


main()
{
	char infix[MAX_SIZE] = {0};
	char postfix[MAX_SIZE] = {0};
	char c = 0;
	int i = 0;
	char *roman = NULL;
	int result = 0;
	
	memset(infix, '\0', sizeof(infix));
	memset(postfix, '\0', sizeof(postfix));
	memset(stack, '\0', sizeof(stack));

	/*
	roman = malloc(3001*sizeof(char *));
	for(i=0; i<=3000; i++)
	{
		roman[i] = malloc(20*sizeof(char));
		memset(&roman[i],'\0',sizeof(char)*20);
		roman[i] = IntToRoman(i);
	}
	*/
	printf("Enter the Infix expression:\n");
	while( (c=getchar()) != '\n')
	{
		if(isspace(c)) continue;
		if(!isdigit(c) && !isRoman(c) && !checkOp(c) && (c != '(') && (c != ')') && (c != '[') && (c != ']'))
		{
			printf("ERROR : Error in expression...\n");
			exit(-1);
		}
		infix[i++] = c;		
	}
	infix[i] = '\0';
	printf("Infix Expression is - %s\n",infix);
	ConvertToPostfix(infix, postfix);
	///////printf("\n\nPostfix Expression is - %s\n",postfix);
	result = Evaluate(postfix);
	//if(result < 0) result = result + '0';
	//result = atoi(&retValue);
	printf("INT Result = %d\n",result);

	if(result > 3000)
	{
		printf("Result > 3000....(LIMIT crossed)\n");
		exit(0);
	}
	roman = IntToRoman(result);
	printf("Roman Result = %s\n",roman);
}

