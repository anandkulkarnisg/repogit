/*
 * heapsort.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: anand
 */

#include<iostream>
using namespace std;
extern void printArr(int*, int);
extern void swapItems(int*, int*);


// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] >= arr[largest])		// switch the comparison to convert the heap structure to either max/min here. This changes the direction of sorting.
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] >= arr[largest])		// switch the comparison to convert the heap structure to either max/min here. This changes the direction of sorting.
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    //cout << "In the middle" << endl;
    //printArr(arr, n);
    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void demoheapSort() {

    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Before" << endl;
    printArr(arr, n);
    heapSort(arr, n);
    cout << "After" << endl;
    printArr(arr, n);

}



