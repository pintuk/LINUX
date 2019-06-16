//#include<iostream.h>

#include<stdio.h>

struct A
{
	//private:
		int x;
	//public:
		//A(int x)
		//{
		//	this->x = x;
		//}
		void Show();
		//{
			//cout << "X = " << x << endl;
		//	printf("X = %d\n",x);
		//}
};

int main()
{
	struct A a;
	a.x = 10;
	//a.Show();
}

