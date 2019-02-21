#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int fiboNacciSearch(const int arr[], const int& itemToBeFound, const int& size)
{
	// Identify a fibonacci number that is just greater than or equal to the array size.
	int fibMM2=0;
	int fibMM1=1;
	int fibM=fibMM1+fibMM2;

	while(fibM<=size)
	{
		fibMM2=fibMM1;
		fibMM1=fibM;
		fibM=fibMM1+fibMM2;
	}

	int offset=-1;
	int index=-1;
	// We keep attempting to find till we run out of fib numbers or we find the item.
	while(fibM>1)
	{
		index=min(offset+fibMM2, size-1);
		if(arr[index]<itemToBeFound)
		{

			// Item is in upper 2/3 range. go down 1 fib level.
			fibM=fibMM1;
			fibMM1=fibMM2;
			fibMM2=fibM-fibMM1;
			offset=index;
		}
		else if(arr[index]>itemToBeFound)
		{
			// Item is in lower 1/3 range. go down 2 fib level.
			fibM=fibMM2;
			fibMM1=fibMM1-fibMM2;
			fibMM2=fibM-fibMM1;
		}
		else
			return(index);
	}

	if(fibMM1 && arr[offset+1]==itemToBeFound)
		return(offset+1);

	return(-1);
}

int main(int argc, char* argv[])
{
	int arr[] = { 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13 };
	size_t size = sizeof(arr)/sizeof(arr[0]);
	int itemToBeFound=5;
	int indexPos = fiboNacciSearch(arr, itemToBeFound, size);
	if(indexPos<0)
		cout << "not found" << endl;
	else
	cout << "Item is found at the index = " << indexPos << endl;
	return(0);
}
