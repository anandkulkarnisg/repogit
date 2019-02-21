#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(int argc, char* argv[])
{
	vector<vector<int>> buckets;
	buckets.reserve(10);
	for(unsigned int i=0; i<=9; ++i)
		buckets[i].reserve(10);

	for(unsigned int i=0; i<=9; ++i)
	{
		buckets[i].clear();
		buckets[i].shrink_to_fit();
	}
	buckets.clear();
	return(0);
}
