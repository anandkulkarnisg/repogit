#include<iostream>
#include<string>
#include<vector>

using namespace std;

void demo1()
{
	vector<vector<int>> buckets;
	buckets.reserve(10);
	size_t size=10, bucketSize=10;

	for(unsigned int i=0; i<bucketSize; ++i)
		buckets.push_back({ });
	for(unsigned int i=0; i<bucketSize; ++i)
		buckets[i].reserve(size);
}

void demo2()
{
    vector<vector<int>> buckets;
    size_t size=10, bucketSize=10;
	
	buckets.resize(bucketSize);
    for(unsigned int i=0; i<bucketSize; ++i)
        buckets[i].reserve(size);
}

int main(int argc, char* argv[])
{
	demo1();
	demo2();
	return(0);
}
