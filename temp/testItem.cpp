#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

template<typename T> T getMax(const T& item1, const T& item2)
{
	std::cout << "Max value of " << item1 << " and " << item2 << " is = " << std::max(item1, item2) << std::endl;
	return(std::max(item1, item2));
}

int main(int argc, char* argv[])
{
	getMax<int>(static_cast<double>(3.5),static_cast<double>(3.64)); 
	return(0);
}
