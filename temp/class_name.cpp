#include <vector>
#include <iostream>
#include <cxxabi.h>
#include <memory>
#define quote(x) #x

template <typename foo,typename bar> class one{ };

std::string classname(const std::type_info& info) 
{
	int status;
	char* rslt=abi::__cxa_demangle(info.name(),0,0,&status); 
	std::string result(rslt);
	free(rslt);
	return result;
}

class BaseClass{ };

int main(int argc,char* argv[]) 
{
	one<int,one<double, int> > A;
	int status;
	char* demangled = abi::__cxa_demangle(typeid(A).name(),0,0,&status);
	std::cout << demangled<<"\t" << std::endl;
	std::cout << quote(A) << std::endl;
	BaseClass b1;
	std::vector<BaseClass> v1;
	std::cout << "class name is = " << classname(typeid(b1)) << std::endl;
	std::cout << "class name is = " << classname(typeid(v1)) << std::endl;
	std::cout << "class name is = " << classname(typeid(std::shared_ptr<BaseClass>(new BaseClass))) << std::endl;
	free(demangled);
	return 0;
}
