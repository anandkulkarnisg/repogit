#include<iostream>
#include<string>
#include<climits>

using namespace std;

int main(int argc, char* argv[])
{
	unsigned int test = 1;
	--test;
	std::cout << test << std::endl;
	--test;
	std::cout << test << std::endl;
	//std::cout << INT_MAX << std::endl;
}
