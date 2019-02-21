#include<iostream>
using namespace std;

void swapItems(int* item1, int* item2)
{

	int temp=*item1;
	*item1=*item2;
	*item2=temp;
}


void printArr(int arr[], int size)
{
	for(int i=0; i<=size-2;++i)
		cout << arr[i] << " , ";
	cout << arr[size-1] << endl;
}


int partition(int arr[], int low, int high)
{

	int pivot=arr[high];
	int i=low-1;

	for(int j=low;j<high;++j)
	{
		if(arr[j] >= pivot)
		{
			++i;
			swapItems(&arr[j], &arr[i]);
		}
	}
	swapItems(&arr[i+1],&arr[high]);
	return(i+1);
}

void quicksort(int arr[], int low, int high)
{
	if(low<high)
	{
		int partitionIdx=partition(arr,low,high);
		quicksort(arr,0,partitionIdx-1);
		quicksort(arr,partitionIdx+1,high);
	}
}

int main(int argc, char* argv[])
{
	int arr[] = { 10, 3, 5, 2, 11 };
	int size = sizeof(arr)/sizeof(arr[0]);
	quicksort(arr,0,size-1);
	printArr(arr,size);
	return(0);
}




