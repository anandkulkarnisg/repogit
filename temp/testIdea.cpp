#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(int argc, char* argv[])
{
	vector<int> testvec;
	testvec.reserve(10);

	testvec.emplace_back(1);
	testvec.emplace_back(2);
	testvec.emplace_back(3);	

	std::cout << "vector size = " << testvec.size() << ", and vector capacity = " << testvec.capacity() << std::endl;
	std::cout << "The first item is at = " << &testvec[0] << std::endl;

	testvec.reserve(20);
	std::cout << "vector size = " << testvec.size() << ", and vector capacity = " << testvec.capacity() << std::endl;
	std::cout << "The first item is at = " << &testvec[0] << std::endl;

	return(0);
}

