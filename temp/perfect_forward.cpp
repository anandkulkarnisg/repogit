#include<iostream>
#include<string>

using namespace std;

class A
{

};

template<typename T> void foo(T item)
{
	std::cout << item << std::endl;
}

template<typename T> void foo(const T& item)
{
	std::cout << "ref " << item << std::endl;
}

template<typename T> void relay(const T&& ref)
{
	foo(std::forward<T>(ref));
}

// below is old world style which does not do perfect forwading. Instead does a copy.

template<typename T> void foo_old(T item)
{
	std:: cout << item << std::endl;
}

template<typename T> void relay_old(T arg)
{
	foo_old(arg);
}

int main(int argc, char* argv[])
{

	int p = 12;
	const int& ref = p;

	relay_old(p);
	relay_old(ref);	

	relay(std::move(p));
	/*
	relay(std::move(ref));
	*/

	return(0);
}
