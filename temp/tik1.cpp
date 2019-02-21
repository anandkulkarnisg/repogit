#include<iostream>
#include<string>

using namespace std;

template<typename T> T func(T& a)
{
	return(a+2);
}

template<typename T> T func(const T& a)
{
	return(a+3);
}


int main(int argc, char*argv[])
{

	int i=5;
	cout << func(i) << endl;	// T& is an accurate match.

	const int j=12;
	cout << func(j) << endl;	// const T& a is more accurate match.

	cout << func(5) << endl; // call the const T& a i.e second one.

	return(0);
}
