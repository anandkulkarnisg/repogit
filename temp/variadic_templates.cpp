#include<iostream>
#include<string>
#include<functional>

using namespace std;

template<typename T> T adder(const T& v) 
{
	return v;
}

template<typename T, typename... Args> T adder(const T& first, Args... args) 
{
	std::cout << "sizeof = " << sizeof...(args) << std::endl;
	return first + adder(args...);
}

template<typename T, typename... Args> T adder2(const T& first , const T& second, Args... args)
{
	return (first + second + adder(args...));
}

template<typename T,typename... Args1, typename... Args2> T adder3(const T& first1, Args1... args1, const T& first2, Args2... args2)
{
	std::cout << "first1 = " << first1 << " , " << "first2 = " << first2 << std::endl;
	adder3(args1..., args2...);
}

int main(int argc, char* argv[])
{
	std::string s1 = "x", s2 = "aa", s3 = "bb", s4 = "yy", s5 = "zz";
	std::string ssum = adder(s1, s2, s3, s4);
	std::cout << "ssum = " << ssum << std::endl;
	std::string ssum2 = adder2(s1, s2, s3, s4, s5);
	std::cout << "ssum2 = " << ssum2 << std::endl;
	return(0);
}
