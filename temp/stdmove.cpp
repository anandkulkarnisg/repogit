#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
	int a=10;
	int b;
	b=std::move(a);
	cout << "b = " << b << endl;
	cout << "a = " << a << endl;

	int* p = new int(12);
	int *q;
	q = std::move(p);
	cout << "q = " << *q << endl;
	cout << "p = " << *p << endl;
}
