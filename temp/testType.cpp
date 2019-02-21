#include<iostream>
#include<string>
#include<typeinfo>
#include <cxxabi.h>
#include<functional>
#include<chrono>
#include<ratio>

using namespace std;

using namespace std::placeholders;

class TempClass
{
	private:
		int m_i = 2;

	public:
		int get() const
		{
			return(this->m_i);
		}
		int gets(const int& i) const
		{
			return(this->m_i + i);
		}
		int getTwo(const int& i, const int& j) const
		{
			return(this->m_i + i + j);
		}
		int getThree(const int& i, const int& j) const
		{
			return(this->m_i + i + j);
		}
};

int main(int argc, char* argv[])
{
	TempClass item;
	int status;
	std::cout << item.get() << std::endl;
	auto callableFunc = &TempClass::get;
	std::string type = abi::__cxa_demangle(typeid(callableFunc).name(), 0, 0, &status);
	std::cout << "type is = " << type << std::endl;
	auto callableFunc2 = &TempClass::gets;
	type = abi::__cxa_demangle(typeid(callableFunc2).name(), 0, 0, &status);
	std::cout << "type is = " << type << std::endl;
	auto callable = std::bind(callableFunc2, &item, 10);
	std::cout << "value = " << callable() << std::endl;
	auto callableFunc3 = &TempClass::getTwo;
	type = abi::__cxa_demangle(typeid(callableFunc3).name(), 0, 0, &status);
	std::cout << "type is = " << type << std::endl;
	auto callableFunc4 = &TempClass::getThree;
	type = abi::__cxa_demangle(typeid(callableFunc4).name(), 0, 0, &status);
	std::cout << "type is = " << type << std::endl;
	auto callable2 = std::bind(callableFunc3, &item, _1, _2);
	auto returnVal = callable2(10,20);
	std::cout << "value = " << returnVal << std::endl;
	auto var = std::chrono::nanoseconds;
	type = abi::__cxa_demangle(typeid(var).name(), 0, 0, &status);
	std::cout << "the type is = " << type << std::endl;
		
}

