#include<iostream>
#include<vector>
#include<string>

using namespace std;

class TestClass
{
	private:
		int m_i;

	public:
		TestClass(int i) : m_i(i) { }
};

int main(int argc, char* argv[])
{
	TestClass t;
	return(0);
}
