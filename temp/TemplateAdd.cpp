#include<iostream>
#include<string>

using namespace std;

template<typename T> T adder(T v) 
{
	if(v%2 == 0)
		return v;
	else
		return(0);
}

template<typename T, typename... Args> T adder(T first, Args ...args) 
{
	if(first%2 == 0)	
		return first + adder(args...);
	else
		return adder(args...);
}

template<typename T>
T pairmul(T a, T b) 
{
  // In real-world code, we wouldn't compare floating point values like
  // this. It would make sense to specialize this function for floating
  // point types to use approximate comparison.
  return (a * b);
}

template<typename T, typename... Args>
T pairmul(T a, T b, Args... args) 
{
  return (a * b) + pairmul(args...);
}

int main(int argc, char* argv[])
{
	cout << adder<int>(1,2,3,4,5,6) << endl;
	cout << adder<int>(1,3,5,7,9) << endl;
	cout << pairmul<int>(1,1,2,2) << endl;
	return(0);
}
