#include<iostream>
#include<string>
#include<chrono>
#include<typeinfo>
#include <cxxabi.h>

using namespace std;

int main(int argc, char* argv[])
{
	//auto duration_return_type = typename std::result_of<std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())>::type;
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << typeid(t1).name() << std::endl;
	char   *realname;
	int status;
	realname = abi::__cxa_demangle(typeid(t1).name(), 0, 0, &status);
	std::cout << "Real Name = " << realname << std::endl;
	auto t2 = std::chrono::high_resolution_clock::now();

	auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
	realname = abi::__cxa_demangle(typeid(diff).name(), 0, 0, &status);
	std::cout << "Real Name = " << realname << std::endl;

	auto t3 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	realname = abi::__cxa_demangle(typeid(t3).name(), 0, 0, &status);
	std::cout << "Real Name = " << realname << std::endl;

	return(0);
}
