#include<iostream>
#include<string>
#include<map>

using namespace std;

int main(int argc, char* argv[])
{
	std::map<const char*,int> m_map;
	m_map["a"] = 1;
	m_map["b"] = 2;
	m_map["c"] = 3;
	m_map["d"] = 5;

	for(const auto& iter : m_map)
		std::cout << "key = " << iter.first << " , value = " << iter.second << std::endl;		

	// Erase everything from the map which is less than 3.
	for(auto& iter : m_map)
	{
		if(iter.second<3)
			m_map.erase(iter.first);		
	}

	for(const auto& iter : m_map)
		std::cout << "key = " << iter.first << " , value = " << iter.second << std::endl;

	return(0);
}
