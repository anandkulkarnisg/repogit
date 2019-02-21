#include <iostream>

template <typename T> void f(T &i) 
{ 
	std::cout << 1 << std::endl; 
}

template <> void f(const int &i) 
{ 
	std::cout << 2 << std::endl; 
}

using namespace std;

int main(int argc, char* argv[]) 
{
	int i = 42;
	f(i);

	const int j = 43;
	f(j);

	return(0);
}

