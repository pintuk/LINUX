#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>



#define TRUE		1
#define FALSE		0
#define STACK_SIZE	10
#define MAX_SIZE	100


char Operator[5] = {'/', '*', '+', '-', '\0'};
char stack[STACK_SIZE];
int stack_top = -1;


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
	int result = 0; int i = 0; int x = 0; int y = 0;

	memset(stack,'\0',sizeof(stack));
	for(i=0; postfix[i] != '\0'; i++)
	{
		c = postfix[i];
		if(isdigit(c))
		{
			PushToStack(c);
		}
		if(checkOp(c))
		{
			x = PopFromStack() - '0';
			y = PopFromStack() - '0';
			switch(c)
			{
				case '+':
					PushToStack((y+x)+'0');
				break;
				case '-':
					PushToStack((y-x)+'0');
				break;
				case '*':
					PushToStack((y*x)+'0');
				break;
				case '/':
					PushToStack((y/x)+'0');
				break;
				default:
				break;
			}
		}
	} /* end for */
	result = PopFromStack() - '0';
	return(result);
}

void ConvertToPostfix(char *infix, char *postfix)
{
	int i = 0; int j = 0; int k = 0;
	char c = '\0';

	memset(stack, '\0', sizeof(stack));
	for(i=0; infix[i]!= '\0'; i++)
	{
		if(isdigit(infix[i]))
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
	char retValue = 0;
	int result = 0;
	
	memset(infix, '\0', sizeof(infix));
	memset(postfix, '\0', sizeof(postfix));
	memset(stack, '\0', sizeof(stack));
	printf("Enter the Infix expression:\n");
	while( (c=getchar()) != '\n')
	{
		if(isspace(c)) continue;
		if(!isdigit(c) && !checkOp(c) && (c != '(') && (c != ')'))
		{
			printf("ERROR : Error in expression...\n");
			exit(-1);
		}
		infix[i++] = c;		
	}
	infix[i] = '\0';
	printf("Infix Expression is - %s\n",infix);
	ConvertToPostfix(infix, postfix);
	printf("\n\nPostfix Expression is - %s\n",postfix);
	result = Evaluate(postfix);
	//if(result < 0) result = result + '0';
	//result = atoi(&retValue);
	printf("Result = %d\n",result);
}
