#include<iostream>
#include<string>

using namespace std;

template<typename T> T func(T a)
{
	return(a+2);
}

template<typename T> T func(T& a)
{
	return(a+3);
}

template<typename T> T func(const T& a)
{
	return(a+4);
}

template<typename T> T func(T* a)
{
	return(*a+5);
}

template<typename T> T func(const T* a)
{
	return(a+6);
}

int main(int argc, char* argv[])
{
	const int* ptr;
	const int i = 10;
	ptr = &i;
	cout << func(ptr) << endl;
	return(0);
}
