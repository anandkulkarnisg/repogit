#include<iostream>
#include<string>

using namespace std;

int arr[] = { 1,2,3,4,5,6,7,8,9,10};

int& setAtIndex(int idx)
{
	return(arr[idx]);
}

int bumpUpTheVal(int idx, int bumpFactor)
{
	return((arr[idx]) * bumpFactor);
}

int main(int argc, char* argv[])
{
	
	int size = sizeof(arr)/sizeof(arr[0]);
	for(int i=0; i<size;++i)
		setAtIndex(i)=bumpUpTheVal(i, i+1);

	for(int i=0;i<size;++i)
		cout << arr[i] << endl;
}
