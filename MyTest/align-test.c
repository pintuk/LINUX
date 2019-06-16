#include <stdio.h>

#define ALIGN(x, a)         (((x) + (a) - 1) & ~((a) - 1))


int main()
{
	unsigned int x,a;
	unsigned int ans = 0;

	printf("Enter value and alignment: ");
	scanf("%d %d", &x,&a);

	ans = ALIGN(x,a);

	printf("Answer: %u\n", ans);

	return 0;
}
