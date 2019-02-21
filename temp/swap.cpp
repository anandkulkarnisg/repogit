#include<iostream>
using namespace std;

void swap(int& item1, int& item2)
{
	item1+=item2;
	item2=item1-item2;
	item1=item1-item2;
}

int main(int argc, char* argv[])
{
	int a=12 , b=17;
	cout << "before a = " << a << " and b = " << b << endl;
	swap(a,b);
	cout << "after  a = " << a << " and b = " << b << endl;
}
