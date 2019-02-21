#include<iostream>
#include<vector>

using namespace std;

template<typename T> T getMax(const T& item1, const T& item2)
{
	if(item1 > item2)
		return(item1);
	else
		return(item2);
}

int main(int argc, char* argv[])
{
	cout << getMax<int>(10, 20) << endl;
	cout << getMax<int>(20.46, 20.48) << endl; // both arguments are converted to int and then become 20 :(
	return(0);
}

