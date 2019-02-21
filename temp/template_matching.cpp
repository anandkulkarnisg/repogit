#include<iostream>
#include<string>

using namespace std;

template<typename T> void addSum(T& a) { std::cout << "1" << std::endl; }

template<typename T> void addSum(const T& a) { std::cout << "2" << std::endl; }

int main(int argc, char* argv[])
{
	addSum(10);
	int a=12;
	addSum(a);
	return(0);
}


