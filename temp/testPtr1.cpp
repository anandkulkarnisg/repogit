#include<iostream>
#include<string>

using namespace std;

void assign(int* ptr)
{
	cout << "ptr = " << ptr << endl;
	*ptr=400;
}

int main(int argc, char* argv[])
{
	int a=20;
	assign(&a);
	cout << "a = " << a << endl;
	return(0);
}
