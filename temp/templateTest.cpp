#include<iostream>
#include<string>

using namespace std;

int rsum()
{
	int a1;
	int a2;
	return(a1+a2);
}


template<typename T> T tsum()
{
	T a1;
	T a2;
	cout << &a1 << " , " << &a2 << endl;
	static int counter = 0;
	counter++;
	cout << "counter = " << counter << endl;
	return(a1+a2);
}

int main(int argc, char* argv[])
{

	for(unsigned int i=1; i<=10; ++i)
	{
		//cout << "rsum = " << rsum() << endl;
		cout << "tsum = " << tsum<int>() << endl;
	}

	return(0);
}

