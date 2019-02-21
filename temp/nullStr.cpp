#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
	std::string testString = nullptr;
	if(!testString)
		std::cout << "Yes!!!" << std::endl;
	if(!testString.empty())
		std::cout << testString << std::endl;
	return(0);
}

