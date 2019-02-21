#include<iostream>
#include<string>
#include<memory>

using namespace std;

class Base 
{


};

class Derived1 : public Base
{


};

class Derived2
{


};

template<typename T1, typename T2> bool isDerived()
{

	bool isDerived = false;
	std::shared_ptr<T1> d(new T1);
	try
	{
		throw d.get();
	}
	catch(T2* b)
	{
		isDerived = true;	
	}
	catch(...)
	{

	}

	return(isDerived);
};

int main(int argc, char* argv[])
{
	cout << isDerived<Derived1,Base>() << endl;
	cout << isDerived<Derived2,Base>() << endl;
	return(0);
}
