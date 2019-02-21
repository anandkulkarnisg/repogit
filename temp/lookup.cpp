#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

int main(int argc, char* argv[])
{

	vector<int> v = { 100, 50, 40, 20, 10 };
	vector<int> alice = { 5, 25, 50, 120 };

	std::vector<int>::iterator low,up;
	for(auto iter : alice)
	{
		low = std::lower_bound(v.begin(), v.end(), iter);
		up = std::upper_bound(v.begin(), v.end(), iter);
		cout << (low-v.begin()) << " , " << (up - v.begin()) << endl;
	}

}
