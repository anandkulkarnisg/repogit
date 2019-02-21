#include<iostream>
#include<string>

using namespace std;

class T
{
	private:
		int m_int;
	public:
		T(const int& ref) : m_int(ref) {}
		~T() 
		{
			cout << "T object destroyed" << endl;
		}
};

class SampleTestClass 
{
	private:
		int m_int;
		T Tobj;
	public:
		SampleTestClass(const int& ref) : m_int(ref) , Tobj(ref) 
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
