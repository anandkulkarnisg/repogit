#include<iostream>
#include<string>
#include<functional>
#include<type_traits>

using namespace std;

int addnum(const int& p, const int& q) 
{
	return(p+q);
}

struct S 
{
    int operator()(int& p, int& q) { return(addnum(p,q)); }
};

int main(int argc, char* argv[])
{
	using type_name = typename std::result_of<S(int&, int&)>::type;
	type_name p = 12;
	if(std::is_same<int,decltype(p)>::value)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	auto callableFunc = std::bind(&addnum, 10, 20);
	std::cout << callableFunc() << std::endl;	

	decltype(callableFunc()) q;
	if(std::is_same<decltype(callableFunc()),type_name>::value)
		std::cout << "Yes!!!!!" << std::endl;
	else
		std::cout << "No!!!!" << std::endl;
}
