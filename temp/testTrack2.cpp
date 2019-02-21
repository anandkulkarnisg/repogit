#include<iostream>
#include<string>
#include<functional>
#include<type_traits>

using namespace std;

template<typename T1, typename T2> auto addSum(const T1& item1, const T2& item2) -> decltype(item1 + item2)
{
	return(item1+item2);	
}

template<typename T1, typename T2> struct S 
{
	auto operator()(const T1& item1, const T2& item2) //-> decltype(item1 + item2) decltype not needed.
	{
		return(addSum<T1,T2>(item1, item1));
	}
};

int main(int argc, char* argv[])
{
	using return_type = typename std::result_of<S<int,long>(const int&, const long&)>::type;

	if(std::is_same<int, return_type>::value)
		std::cout << "Yes they are the same" << std::endl;
	else
		std::cout << "No they are not the same" << std::endl;

	if(std::is_same<long, return_type>::value)
		std::cout << "Yes they are the same" << std::endl;
	else
		std::cout << "No they are not the same" << std::endl;

	auto callableFunc = std::bind(&addSum<std::string, std::string>, "Anand ", "Apparao Kulkarni");
	std::cout << callableFunc() << std::endl;
	
	decltype(callableFunc()) pString = callableFunc();
	std::cout << "pString = " << pString << std::endl;
	
	return(0);
}

