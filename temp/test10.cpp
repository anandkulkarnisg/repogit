#include<iostream>
#include<string>

using namespace std;

class SampleClass
{

	private:
		int a;

	public:
		SampleClass() : a(12) { cout << "1" << endl; }
		SampleClass(const SampleClass& copyObj) { this->a = copyObj.a; cout << "2" << endl; }
		~SampleClass() { cout << "3" << endl; }
};

SampleClass h()
{
	SampleClass a;
	return(a);
}

SampleClass g()
{
	return(h());
}

SampleClass f()
{
	return(g());
}

// g++ -fno-elide-constructors test10.cpp -o noelide.out
// g++ test10.cpp -o elided.out
// 1 2 3 2 3 2 3 2 3 3 -> elision disabled output.
// 1 2 3 3 -> copy elision enabled by default in g++. 

int main(int argc, char* argv[])
{
	SampleClass a = f();
	return(0);
}
