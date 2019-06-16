#include<iostream.h>

//using namespace std;

int global = 100;

class A
{
	private:
		int a1;
		int a2;
		int c2;
	public:
		A()
		{
			a1 = 2;
			a2 = 3;
			c2 = a1 + a2;
			cout << "Default Constructor called !!! " <<endl;
		}
		A(int x)
		{
			a1 = x;
			a2 = 0;
			c2 = a1 + a2;
			cout << "Constructor called(1 arg) !!! " <<endl;
		}
		A(int a1, int a2)
		{
			this->a1 = a1;
			this->a2 = a2;

			this->c2 = this->a1 + this->a2;

			cout << "User Constructor called !!! " <<endl;
		}
		void Add(int a, int b)
		{
			a1 = a;
			a2 = b;

			c2 = a1+a2;

			cout << "Add() called !!! " << endl;
		}
		void Display();
		~A()
		{
			int global = 10;
			a1 = 0;
			a2 = 0;
			c2 = 0;

			cout << "Global = " << ::global << endl;
			cout << "Default Destructor called !!! " << endl;
		}
};

void A::Display()
{
	cout << "Sum = " << c2 << endl;

}

main()
{
	int a = 5; 
	int b = 6;

	char str[] = "Hello";

	//A add; A add2;
	A add(10);
	//A add(a,b);

	//add.Add(11, 9);
	add.Display();
}

