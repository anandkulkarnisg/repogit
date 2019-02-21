#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

int doJumpSearch(const int arr[], const int& itemToBeSearched, const size_t& size)
{
	// jump size is always square root of the size of array.	
	int jumpSize = sqrt(size);

	// start at index = 0 and keep jumping in size of jumpSize until the item searched is less than the item at jump index.
	int startIdx = 0;
	while(startIdx<=size-1)
	{
		if(arr[startIdx]<itemToBeSearched)
			startIdx+=jumpSize;		
		else if(arr[startIdx]>itemToBeSearched)
			break;
		else 
			return(startIdx);			
	}

	if(startIdx<=0)
		return(-1);

	startIdx-=jumpSize;

	int lowerBound=startIdx;
	int upperBound=min(startIdx+jumpSize, static_cast<int>(size-1));

	for(unsigned int i=lowerBound; i<=upperBound; ++i)
	{
		if(arr[i]==itemToBeSearched)
			return(i);
	}
	return(-1);
}

int main(int argc, char* argv[])
{
	int arr[] =  { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
	size_t size = sizeof(arr)/sizeof(arr[0]);
	for(unsigned int i=0; i<size; ++i)
	{
		int itemToBeSearched = arr[i];
		int idxPos = doJumpSearch(arr, itemToBeSearched, size);
		if(idxPos<0)
			cout << "item = " << itemToBeSearched << " is not found" << endl;
		else
			cout << "item = " << itemToBeSearched << " is found at index = " << idxPos << endl;
	}
	return(0);
}
