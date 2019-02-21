#include<iostream>
#include<string>
#include<type_traits>

using namespace std;

int main(int argc, char* argv[])
{
	if(is_same<string, string>::value)
		std::cout << "yes!!!!" << std::endl;
}
