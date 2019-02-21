#include<iostream>
#include<string>
#include<tuple>

using namespace std;

int main(int argc, char* argv[])
{
	tuple<std::string, double, int> t("foo", 3.14, 7);
	std::cout << get<int>(t) << std::endl;
	std::cout << get<std::string>(t) << std::endl;
	std::cout << get<double>(t) << std::endl;
	return(0);
}
