/*
 * insertionsort.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: anand
 */

#include<iostream>
#include<string>
using namespace std;
extern void printArr(int*, int);
extern void swapItems(int*, int*);

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;

       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && arr[j] > key) // switch the direction of arr[j] and key comparison to sort other way.
       {
    	   //cout << "swapping the " << (j+1) << "with element from" << j << " position" << endl;
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
       //cout << "inserting " << key << " at arr[" << (j+1) << "]" << endl;
       //cout << "Now array is : " << endl;
       //printArray(arr, n);
   }
}

void demoInsertionSort() {

    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Before" << endl;
    printArr(arr, n);
    insertionSort(arr, n);
    cout << "After" << endl;
    printArr(arr, n);

}




