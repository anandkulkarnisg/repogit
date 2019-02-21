#include<iostream>
#include<string>
#include <stdexcept> 

using namespace std;

int main(int argc, char* argv[])
{
	std::string sampleString = "Anand";
	try
	{
		std::cout << std::stoi(sampleString) << std::endl;
	}
	catch(const std::invalid_argument& e)
	{
		std::cout << "Exception message = " << e.what() << std::endl;
	}
	return(0);
}

