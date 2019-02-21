#include<iostream>
#include<string>
#include<chrono>
#include<ratio>
#include<cxxabi.h>
#include<typeinfo>
#include<thread>

using namespace std;

void waitTime(const chrono::duration<_Rep, _Period>& waitTime)
{
	std::this_thread::sleep_for(waitTime);
}

int main(int argc, char* argv[])
{
	auto item = std::chrono::milliseconds(10);
	int status;
	std::string realname = abi::__cxa_demangle(typeid(item).name(), 0, 0, &status);
	std::cout << realname << std::endl;
	std::chrono::duration<long, std::ratio<1l, 1000l>> item2;
	
}


