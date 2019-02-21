#include <iostream>
#include<string>

using namespace std;

class A 
{
	public:
		A() { cout << "constructed a" << endl;  }
		~A() { cout << "A" << endl; }
};

int i = 1;

int main(int argc, char* argv[]) 
{
	cout << "This is before the label start" << endl;
label:
	cout << "This is first statement after label start" << endl;
	A a;
	if (i--)
	{
		cout << "This is just before jump instruction" << endl;
		goto label;
		cout << "This is just after jump instruction" << endl;
	}
}
