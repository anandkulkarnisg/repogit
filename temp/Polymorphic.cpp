#include<iostream>
#include<string>

using namespace std;

class A
{
	private:
		int a;
		void sampleFunc() { }
};

class B
{
	private:
		int a;
		virtual void sampleFunc() { }
};


class C { int x; void virtual f() { }  };
class D : public C { };

int main(int argc, char* argv[])
{
	cout << sizeof(C) << " , " << sizeof(D) << endl;
	return(0);
}
