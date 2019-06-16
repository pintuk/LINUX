#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>



#define TRUE		1
#define FALSE		0
#define STACK_SIZE	100
#define MAX_SIZE	100


char Operator[5] = {'/', '*', '+', '-', '\0'};
char stack[10][STACK_SIZE];
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
	char *ptr = stack[0];

	if(ptr == NULL || stack[0][0] == '\0') return(TRUE);

	return(FALSE);
}

char * PopFromStack()
{
	char *op = NULL;

	if(!StackIsEmpty())
	{
		op = stack[stack_top];
		//stack[stack_top] = '\0';
		memset(&stack[stack_top], '\0', sizeof(&stack[stack_top]));
		stack_top--;
	}
	return(op);
}

void PushToStack(char *op)
{
	if(StackIsEmpty()) 
	{
		stack_top = -1;
		memset(&stack, '\0', sizeof(&stack));
	}
	//stack_top = stack_index;
	strcpy(stack[++stack_top],op);
}

int Evaluate(char *postfix)
{
	char c = '\0';
	int result = 0; int i = 0; int j = 0; int x = 0; int y = 0;
	char *data = NULL;
	int value = 0;

	memset(&stack,'\0',sizeof(&stack));
	data = malloc(sizeof(postfix));
	//value = malloc(sizeof(postfix));
	memset(data,'\0',sizeof(postfix));
	for(i=0; postfix[i] != '\0'; i++)
	{
		c = postfix[i];
		if(isdigit(c))
		{
			memset(data,'\0',sizeof(postfix));
			sprintf(data,"%d",c);
			PushToStack(data);
		}
		if(checkOp(c))
		{
			x = atoi(PopFromStack());
			y = atoi(PopFromStack());
			switch(c)
			{
				case '+':
					value = y+x;
					memset(data,'\0',sizeof(postfix));
					sprintf(data,"%d",value);
					PushToStack(data);
				break;
				case '-':
					value = y-x;
					memset(data,'\0',sizeof(postfix));
					sprintf(data,"%d",value);
					PushToStack(data);
				break;
				case '*':
					value = y*x;
					memset(data,'\0',sizeof(postfix));
					sprintf(data,"%d",value);
					PushToStack(data);
				break;
				case '/':
					value = y/x;
					memset(data,'\0',sizeof(postfix));
					sprintf(data,"%d",value);
					PushToStack(data);
				break;
				default:
				break;
			}
		}
		if(c == '[')
		{
			i++; j = 0;
			memset(data,'\0',sizeof(postfix));
			while(postfix[i] != ']')
			{
				data[j++] = postfix[i++];
			}
			data[j] = '\0';
			PushToStack(data);
		}
	} /* end for */
	result = atoi(PopFromStack());
	return(result);
}

void ConvertToPostfix(char *infix, char *postfix)
{
	int i = 0; int j = 0; int k = 0;
	char c = '\0';
	char *data = NULL;

	memset(&stack, '\0', sizeof(&stack));
	data = malloc(sizeof(infix));
	memset(data,'\0',sizeof(infix));
	for(i=0; infix[i]!= '\0'; i++)
	{
		if(isdigit(infix[i]))
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
				sprintf(data,"%c",infix[i]);
				PushToStack(data);
				continue;
			}
			//if(!StackIsEmpty() && (stack[stack_top] == '('))
			//{
			//	PushToStack(infix[i]);
			//	continue;
			//}
			while(!StackIsEmpty())
			{
				if (OpPrecedence(*stack[stack_top]) >= OpPrecedence(infix[i]))
				{
					postfix[j++] = PopFromStack()[0];
				}
				else
				{
					//PushToStack(infix[i]);
					break;
				}
			}
			sprintf(data,"%c",infix[i]);
			PushToStack(data);
		}
		else if(infix[i] == '(')
		{
			sprintf(data,"(");
			PushToStack(data);
		}
		else if(infix[i] == ')')
		{
			while( (c = PopFromStack()[0]) != '(')
			{
				postfix[j++] = c;
			}
		}
	}
	while(!StackIsEmpty())
	{
		postfix[j++] = PopFromStack()[0];
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
	memset(&stack, '\0', sizeof(&stack));
	printf("Enter the Infix expression:\n");
	while( (c=getchar()) != '\n')
	{
		if(isspace(c)) continue;
		if(!isdigit(c) && !checkOp(c) && (c != '(') && (c != ')') && (c != '[') && (c != ']'))
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
	//result = Evaluate(postfix);
	//if(result < 0) result = result + '0';
	//result = atoi(&retValue);
	//printf("Result = %d\n",result);
}

