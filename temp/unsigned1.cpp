#include<iostream>
#include<string>

using namespace std;

unsigned int sampleFunc(const unsigned int& param)
{
	return(param);
}	

int main(int argc, char* argv[])
{
	std::cout << "sampleFunc value = " << sampleFunc(-10) << std::endl;
	return(0);
}
