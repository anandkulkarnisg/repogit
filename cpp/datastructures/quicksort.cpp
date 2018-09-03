/*
 * quicksort.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: anand
 */


// Good resources.
// https://www.youtube.com/watch?v=COk73cpQbFQ
// http://www.geeksforgeeks.org/quick-sort/

#include<iostream>
using namespace std;
extern void printArr(int*, int);
extern void swapItems(int*, int*);

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)	// switch the comparison here to sort the other way.
        {
            i++;    // increment index of smaller element
            swapItems(&arr[i], &arr[j]);
        }
    }
    swapItems(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void demoquickSort() {

    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Before" << endl;
    printArr(arr, n);
    quickSort(arr, 0, n-1);
    cout << "After" << endl;
    printArr(arr, n);

}


