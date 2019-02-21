#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(int argc, char* argv[])
{
	vector<int> testVec;
	testVec.reserve(34);
	testVec[29]=12;
	std::cout << "vector size = " << testVec.size() << std::endl;
	std::cout << testVec[29] << std::endl;
	return(0);
}

