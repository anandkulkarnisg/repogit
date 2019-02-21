#include<iostream>
#include<string>

using namespace std;

template<typename T,int n> class TestEvenOdd
{
	public:
		enum { value=0 };	
};

template<typename T, int p> class RecursiveTemplateAdd
{
	enum { value=TestEvenOdd<T,p>::value + RecursiveTemplateAdd<T,p-1>::value }; 
};

template<typename T> class RecursiveTemplateAdd<T,0>
{
	public:
		enum { value=0 };
};


int main(int argc, char* argv[])
{
	cout << TestEvenOdd<int,10>::value << endl;
}
