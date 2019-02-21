#include<iostream>
#include<string>
#include<type_traits>

using namespace std;

class A
{

};

int main(int argc, char* argv[])
{
	A obj;
	A& ref = obj;
	const A& ref2 = obj;

	if(std::is_lvalue_reference<decltype(obj)>::value)
		std::cout << "Yes A is lvalue reference" << std::endl;

	if(std::is_lvalue_reference<decltype(ref)>::value)
		std::cout << "Yes A& it is a lvalue reference" << std::endl;

	if(std::is_lvalue_reference<decltype(ref2)>::value)
		std::cout << "Yes const A& it is a lvalue reference" << std::endl;

	return(0);
}
