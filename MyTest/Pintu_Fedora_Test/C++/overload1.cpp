#include<stdio.h>
#include<iostream.h>

void Show(int a = 0, int b = 1)
{
	cout << "a = " << a << "  b = " << b << endl;
}

void Display(int x)
{
	cout << "Display(int) = " << x << endl;
}

void Display(char x)
{
	cout << "Display(char) = " << x << endl;
}


int main()
{
	Show(2);
	Display('A');
}

