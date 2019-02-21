#include<iostream>
#include<string>

using namespace std;

struct A
{
	A()
	{
		throw 2;
	}
};

struct B
{
	B()

		try
		{
			A a;
		}
	catch(int i)
	{
		cout << i << endl;
	}
};

int main(int argc, char* argv[])
{
	B b;
	cout << "3" << endl;
	return(0);
}
