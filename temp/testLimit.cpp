#include<iostream>
#include<string>
#include<climits>

using namespace std;

auto sum(int a, int b)
{
	return(a+b);
}

long sum1(const int& a, const int& b)
{
	return(static_cast<long>(a) + static_cast<long>(b));
}


template<typename T1, typename T2> T2 tsum(const T1& a, const T2& b)
{
	return(static_cast<T2>(a) + static_cast<T2>(b));
}

template<typename T> T retsum()
{
	T p1;
	T p2;
	return(p1+p2);
}

int main(int argc, char* argv[])
{
	int a = INT_MAX - 1;
	int b = INT_MAX - 2;
	auto c = (a + b); // fails to identify the type of a + b as long.
	cout << a << " , " << b << "," << c << endl;
	decltype(a+b) d = a + b; // same here.
	cout << d << endl;
	cout << static_cast<long>(a + b) << endl; // does not work either. (a+b) is already screwed before casting.
	long long r = static_cast<long long>(a) + static_cast<long long>(b); // It works now.
	long r1 = static_cast<long>(a) + static_cast<long>(b); // works!
	cout << r << endl;
	cout << r1 << endl;
	cout << sum(INT_MAX-1, INT_MAX-2) << endl;
	cout << sum1(INT_MAX, INT_MAX) << endl;
	cout << tsum<int,long>(INT_MAX, INT_MAX) << endl;
	cout << tsum<int,int>(INT_MAX, INT_MAX) << endl;
	cout << "rand print = " << retsum<int>() << endl;
	cout << "rand print = " << retsum<int>() << endl;
	for(unsigned int i=1; i<=10; ++i)
		cout << retsum<int>() << endl;
	cout << retsum<int>()-retsum<int>() << endl;
	return(0);
}
