#include<iostream>
#include<string>
#include<map>

using namespace std;

template<typename T1, typename T2> class TestClass
{
	private:
		std::map<T1,T2> m_map;
	public:
		void put(const std::pair<T1,T2>& pairRef)
		{
			m_map[pairRef.first] = pairRef.second;	
		}
		T2 get(const T1& keyItem)
		{
			return(m_map.find(keyItem)->second);
		}
};

int main(int argc, char* argv[])
{
	TestClass<std::string, std::string> testObj;
	std::cout << testObj.get("anand") << std::endl;
}


