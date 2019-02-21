#include<iostream>
#include<vector>
#include<string>

using namespace std;


int main(int argc, char* argv[])
{
	vector<int> vec = { 10, 2, 3, 4, 5 };
	vector<int>::const_iterator it1 = vec.begin();
	it1--;

	vector<int>::const_reverse_iterator it2 = vec.rend();
	if( *it1 == *it2)
	{
		cout << "Yes they are same!" << endl;
		cout << *it1 << endl;
	}
	return(0);
}
