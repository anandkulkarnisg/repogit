#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{

	std::string textLine = "10,2050";
	std::cout << textLine.c_str() << std::endl;
	std::size_t findPos = textLine.find(",");
	int firstItem = std::stoi(textLine.substr(0, findPos));
	int secondItem = std::stoi(textLine.substr(findPos+1,textLine.length()-1));
	std::cout << "firstItem = " << firstItem << std::endl;	
	std::cout << "secondItem = " << secondItem << std::endl;
	return(0);
}

