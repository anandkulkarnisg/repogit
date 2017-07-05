/*
 * shellsort.cpp
 *
 *  Created on: Jul 1, 2017
 *      Author: anand
 */

#include<iostream>
using namespace std;
extern void printArr(int*, int);
extern void swapItems(int*, int*);

void shellsort(int arr[], int size)
{
   int i, j, k;
    for (i = size / 2; i > 0; i = i / 2)
    {
        for (j = i; j < size; ++j)
        {
            for(k = j - i; k >= 0; k = k - i)
            {
                if (arr[k+i] >= arr[k])		// switch the comparison here to sort the other way around.
                    break;
                else
                	swapItems(&arr[k], &arr[k+i]);
            }
        }
    }
}

void demoShellSort()
{
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Before" << endl;
    printArr(arr, n);
    shellsort(arr, n);
    cout << "After" << endl;
    printArr(arr, n);

}


