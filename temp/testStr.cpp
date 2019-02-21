#include<iostream>
#include<string>

using namespace std;

bool isStringNull(void* dataPtr)
{
	if(dataPtr == nullptr)
		std::cout << "The dats is null" << std::endl;
	else
	{
		std::string str = static_cast<std::string>(*dataPtr);
		std::cout << "str = " << str << std::endl;
	}
	return(true);		
}


int main(int argc, char* argv[])
{
	return(0);
}
