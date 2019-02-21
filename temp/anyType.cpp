#include<iostream>
#include<string>
#include<map>
#include<type_traits>
#include<functional>

using namespace std;

std::map<std::string, std::string> m_configMapItems;

template<typename T> T getTvalue(const std::string& key, const T& defaultVal)
{
	T returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		// Case of bool.
		if(std::is_same<T, bool>::value)		
		{
			if(iter->second == "true" || iter->second == "1")
				returnVal=true;
		}

		// Case for the long.
		if(std::is_same<T,long>::value)
		{
			try
			{
				returnVal = std::stol(iter->second);
			}
			catch(const std::invalid_argument& e)
			{
				std::cout << "Exception happened while converting " << iter->second << " Into a long value." << std::endl;
			}
		}
	}
	return(returnVal);
}

auto func(const int& p) -> decltype(p+2)
{
	return(p+2);
}

int main(int argc, char* argv[])
{
	m_configMapItems["ConnectionMaxAllowed"]="true";
	m_configMapItems["LongWaitTimeSecs"]="13567812";

	bool configStatus = getTvalue<bool>("ConnectionMaxAllowed", false);
	if(configStatus)
		std::cout << "Yes config is true" << std::endl;
	else
		std::cout << "False config is not true" << std::endl;

	long testStatus = getTvalue<long>("LongWaitTimeSecs", 420.123);
	std::cout << "testStatus = " << testStatus << std::endl;

	decltype(getTvalue<long>("Anand",12345)) testType;
	decltype(testStatus) p;
	if(std::is_same<decltype(testType), decltype(testStatus)>::value)
		std::cout << "Works!" << std::endl;
	else
		std::cout << "does not work!" << std::endl;
	return(0);
}
