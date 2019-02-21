// C++ program to remove duplicates in-place
#include<iostream>
using namespace std;

// Function to remove duplicate elements
// This function returns new size of modified
// array.
int removeDuplicates(int arr[], int n)
{
	if (n==0 || n==1)
		return n;

	// To store index of next unique element
	int j = 0;

	// Doing same as done in Method 1
	// Just maintaining another updated index i.e. j
	for (int i=0; i < n-1; i++)
	{
		if (arr[i] != arr[i+1])
		{
			arr[j] = arr[i];
			j++;
		}
	}

	arr[j] = arr[n-1];
	j++;

	return j;
}

// Driver code
int main()
{
	//int arr[] = {1,2,2,3,4,4,4,5,6,6,7,8,9,9};
	int arr[] = { 1, 2 ,2 ,3 ,3, 3, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// removeDuplicates() returns new size of
	// array.
	n = removeDuplicates(arr, n);

	// Print updated array
	for (int i=0; i<n; i++)
		cout << arr[i] << " ";

	return 0;
}

