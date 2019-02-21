#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<memory>

using namespace std;

class TestPair
{
	private:
		std::string m_name;
		int m_age;

	public:
		TestPair() { }
		TestPair(const std::string& refName, const int& age) : m_name(refName) , m_age(age) { }
		TestPair(const TestPair& copyItem) : m_name(copyItem.m_name) , m_age(copyItem.m_age) { }
		void show() const { std::cout << m_name << "," << m_age << std::endl; }
};

int main(int argc, char* argv[])
{
	std::unordered_map<int,TestPair> myHashMap;	
	myHashMap[0]=TestPair("Anand",10);
	myHashMap[1]=TestPair("Apparao",20);
	myHashMap[2]=TestPair("Kulkarni",30);	

	for (auto& x : myHashMap) 
	{
		std::cout << "Key = " << x.first << ": " << std::endl;
		TestPair obj = x.second;
		obj.show();	
	}

	return(0);
}
