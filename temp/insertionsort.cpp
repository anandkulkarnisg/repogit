#include<iostream>
#include<string>

using namespace std;

void printArr(int arr[], int n)
{
	for(unsigned int i=0; i<=n-2; ++i)
		cout << arr[i] << " , ";
	cout << arr[n-1] << endl;
}

void insertionSort(int arr[], int n)
{
	for(int i=1; i<n; ++i)
	{
		int key=arr[i];
		int j=i-1;
		
		while(j>=0 && arr[j] > key) // flip the arr[j] > key to sort other way. > makes the arr ascending and < makes it descending.
		{
			arr[j+1] = arr[j];
			j--;
		}
			arr[j+1]=key;
	}
}



int main(int argc, char* argv[])
{
	int arr[] = { 12, 13, 17, 5, 6 };
	int size = sizeof(arr)/sizeof(arr[0]);
	cout << "size = " << size << endl;
	cout << "before = " << endl;	
	printArr(arr, size);
	insertionSort(arr, size);
	cout << "after = " << endl;
	printArr(arr, size);
}

