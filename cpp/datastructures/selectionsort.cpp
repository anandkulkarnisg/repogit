/*
 * selectionsort.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: anand
 */

#include<iostream>
using namespace std;
extern void printArr(int*, int);
extern void swapItems(int*, int*);

/* Function to sort an array using insertion sort*/
void selectionSort(int arr[], int size)
{
	for(int i=0; i<size-1; ++i)
	{
		int min=i;
		for(int j=(i+1); j<=size-1;++j)
		{
			if(arr[j]<arr[min])	// switch the comparison to sort the other way.
				min=j;
		}
		if(min != i)
			swapItems(&arr[min], &arr[i]);
	}
}

void demoselectionSort() {

    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Before" << endl;
    printArr(arr, n);
    selectionSort(arr, n);
    cout << "After" << endl;
    printArr(arr, n);

}

