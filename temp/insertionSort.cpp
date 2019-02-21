#include<iostream>
#include<string>

using namespace std;

void printArray(int arr[], int size)
{
	for(int i=0; i<=(size-2); ++i)
		cout << arr[i] << " , ";
	cout << arr[size-1] << endl;
}

void insertionSort(int arr[], int size)
{
	for(int i=1; i<size; ++i)
	{
		int key=arr[i];
		int j=i-1;
		while(j>=0 && arr[j]>key)
		{
			arr[j+1]=arr[j];
			j=j-1;
		}
		arr[j+1]=key;
	}
}

int main(int argc, char* argv[])
{
	int arr[] = { 7, 2, 1};
	int size = sizeof(arr)/sizeof(arr[0]);
	cout << "before array = " << endl;
	printArray(arr, size);
	insertionSort(arr, size);
	cout << "after array = " << endl;
    printArray(arr, size);


}


