#include<iostream>
#include<string>

using namespace std;

class SampleTestClass 
{
	private:
		int m_int;
	public:
		SampleTestClass(const int& ref) : m_int(ref) 
	{ 
		throw 12;
	}
};

int main(int argc,char * argv[])
{
	try 
	{
		SampleTestClass* pObj = new SampleTestClass(12);
	} 
	catch(const int& e)
	{
		cout << "Exception caught here with value = " << e << endl;	
	}
}
