#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

enum class SortOrder { ascending, descending };

SortOrder getSortOrder(const int arr[], const int& size)
{
	for(int i=0; i<size-1; ++i)
	{
		if(arr[i+1]>arr[i])
			return(SortOrder::ascending);
		if(arr[i+1]<arr[i])
			return(SortOrder::descending);    
	}
	return(SortOrder::ascending);
}

bool doCompare(const int& item1, const int& item2, const SortOrder& sortOrder)
{
	if(sortOrder==SortOrder::ascending)
		return(item1<item2);
	else
		return(item1>item2);
}

int doFibonacciSearch(const int arr[], const int& itemToBeFound, const int& size, const SortOrder& sortOrder)
{
	// First we generate the fibonacci number which is either equal/greater than size of array.
	int fibM , fibM1, fibM2;
	fibM2=0, fibM1=1, fibM=fibM1+fibM2;

	while(fibM <= size)
	{
		fibM2=fibM1;
		fibM1=fibM;
		fibM=fibM1+fibM2;    
	}

	int offset=-1;
	int i=0;

	while(fibM>1)
	{
		i=min(offset+fibM2, size-1);

		if(doCompare(arr[i], itemToBeFound, sortOrder))
		{
			// The item is in upper range. reduce fib series 1 level down.
			fibM=fibM1;
			fibM1=fibM2;
			fibM2=fibM-fibM1;
			offset=i;
		}
		else if(doCompare(itemToBeFound, arr[i], sortOrder))
		{
			// The item is in lower range. reduce the fib series 2 level down.
			fibM=fibM2;
			fibM1=fibM1-fibM2;
			fibM2=fibM-fibM1;      
		}
		else
			return(i);
	}

	if(fibM1 && arr[offset+1]==itemToBeFound)
		return(offset+1);

	return(-1);
}

int main(int argc, char* argv[])
{
	//int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };  
	//int arr[] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };  
	int arr[] = { 10, 10, 10, 10, 10 }; // works but item is found at the middle since search is done via 1/3,2/3 division of arrays as portions.
	size_t size = sizeof(arr)/sizeof(arr[0]);
	SortOrder sortOrder = getSortOrder(arr, size);
	int itemToBeFound=10;
	int posIdx=doFibonacciSearch(arr, itemToBeFound, size, sortOrder);
	if(posIdx<0)
		cout << "The item = " << itemToBeFound << " is not found in the array" << endl;
	else
		cout << "The item = " << itemToBeFound << " is at the index = " << posIdx << endl;
	return(0);
}
