#include<iostream.h>

struct A
{
	//private:
		int x;
	//public:
		A(int x)
		{
			this->x = x;
		}
		void Show()
		{
			cout << "X = " << x << endl;
		}
};

int main()
{
	A a(5);
	a.x = 10;
	a.Show();
}

