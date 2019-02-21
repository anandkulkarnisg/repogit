#include<iostream>
#include<string>

using namespace std;


template<typename T> void func(T* a)
{
	*a = *a*2;
}


void func2(int* b)
{
	*b=(*b)*2;
}

int main(int argc, char* argv[])
{
	int i=10;
	int* ptr = &i;
	func(ptr);
	cout << i << endl;

	int p=20;
	func2(&p);
	cout << p << endl;
	return(0);
}

