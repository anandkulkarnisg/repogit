#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

void printArrayToConsole(const int arr[], const char* phase, const size_t& size)
{
	cout << phase << endl;
	for(unsigned int i=0; i<size-1;++i)
		cout << arr[i] << ", ";
	cout << arr[size-1] << '\n';
}

int main(int argc, char* argv[])
{
	int arr[] = { 0, 1, 2, 1, 2, 1, 2, 0, 0, 0, 2, 1, 2, 1, 2, 0, 2, 1, 1 };
	const size_t size = sizeof(arr)/sizeof(arr[0]);
	unsigned int countMap[3];

	for(unsigned int i=0; i<3; ++i)
		countMap[i]=0;

	printArrayToConsole(arr, "before : ", size);

	for(unsigned int i=0; i<size; ++i)
	{	
     if(arr[i]==0)
		countMap[0]+=1;
	 if(arr[i]==1)
		countMap[1]+=1;
	}

	countMap[2]=size-countMap[0]+countMap[1];

	for(unsigned int i=0; i<countMap[0]; ++i)
		arr[i]=0;
	for(unsigned int i=countMap[0]; i<countMap[0]+countMap[1]; ++i)
		arr[i]=1;
    for(unsigned int i=countMap[0]+countMap[1]; i<size; ++i)
		arr[i]=2;

	printArrayToConsole(arr, "after : ", size);
	return(0);
}
