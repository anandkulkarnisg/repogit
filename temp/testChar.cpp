#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
	const char* str1 = "Anand";
	const char* str2 = "Anant";

	std::cout << (str1<str2) << std::endl;
	return(0);
}
