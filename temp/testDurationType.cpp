#include<iostream>
#include<string>
#include<chrono>
#include<typeinfo>
#include<cxxabi.h>

using namespace std;

std::string classname(const std::type_info& info)
{
    int status;
    char* rslt=abi::__cxa_demangle(info.name(),0,0,&status);
    std::string result(rslt);
    free(rslt);
    return result;
}

int main(int argc, char* argv[])
{
	auto duration = std::chrono::hours(2);
	cout << classname(typeid(duration)) << endl;
	return(0);
}

