#include <iostream>
#include <string>
#include <future>

int main() 
{
	std::string x = "x";

	std::async(std::launch::async, [&x]() {x = "y"; std::cout << x << std::endl; });
	std::async(std::launch::async, [&x]() { x = "z";std::cout << x << std::endl; });
	std::cout << "x via main = " << x << std::endl;
	return(0);
}

