#include<iostream>
#include<string>
#include<type_traits>

using namespace std;

int main(int argc, char* argv[])
{
	// No matter how many braces you put across the decltype decltype of a ref cant get any better :).
	int i, &j=i;
	i=10;
	cout << is_same<decltype((((j)))), decltype(j)>::value << endl;
	return(0);	
}
