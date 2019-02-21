#include<iostream>
#include<string>

using namespace std;

class B 
{
	public:
		virtual ~B() { }
};

class D : public B 
{
	public:
		~D() { }
};

int main(int argc,char* argv[])
{
	B* bObj = new D; 
	delete bObj;
}

