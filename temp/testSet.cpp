#include<iostream>
#include<string>
#include<map>

using namespace std;

int main(int argc, char* argv[])
{
	std::map<int,std::string> testMap;
	testMap[1] = "Anand";
	testMap[2] = "Apparao Kulkarni";

	// This attempt below is futile , wont update/add to the map.
	testMap.insert(std::make_pair<int,std::string>(1,"Alberta US"));

	// testMap[1] = "Albert";

	for(const auto& iter : testMap)
		std::cout << "key = " << iter.first << " , value = " << iter.second << std::endl;	

	return(0);
}

