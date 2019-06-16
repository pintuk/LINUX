#include<stdio.h>

main()

{

struct
{
int x;
struct xx *pp;
struct yy
{
char s;
struct xx *p;
}Y;
struct yy *q;
}X;

	X.Y.s = 1;
	printf("X.Y.x = %d\n",X.Y.s);

}
