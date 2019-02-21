#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<typename T> void filter(T f, vector<int> array)
{
	for(auto i : array)
	{
		if(f(i))
			cout << i << endl;
	}
}

int main(int argc, char* argv[])
{
	vector<int> vec = { 1, 2, 3, 4, 5, 6 };
	filter([] (int x){ return x>3; }, vec); // All items greater than 3.
	filter([] (int x){ return(x<2 || x>3); }, vec); // All items less than 2 or greater than 3.
	filter([] (int x){ return(x%2); }, vec); // Find all odd items. 
	filter([] (int x){ return(x%2==0);}, vec); // Find all even items.

	// Using lambda to remove certain items from an array.
	vec.erase(std::remove_if(vec.begin(), vec.end(), [] (int x){ return x>3; }), vec.end());
	cout << "After erasure the vector is now" << endl;
	for(auto iter : vec)
		cout << iter << endl;

	return(0);
}
