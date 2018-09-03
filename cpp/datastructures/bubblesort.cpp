/*
 * bubblesort.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: anand
 */

#include<iostream>
#include<string>
using namespace std;
extern void printArr(int*, int);
extern void swapItems(int*, int*);

void bubbleSort(int arr[], int size) {

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size-(i+1); ++j) {

			if (arr[j] > arr[j+1]) {  // switch the comparison direction to sort the other way.
				swapItems(&arr[j], &arr[j+1]);
			}
		}
	}
}

void demobubbleSort() {

	int arr[] = { 12, 11, 13, 5, 6};
	int size = sizeof(arr)/sizeof(arr[0]);
	cout << "Before" << endl;
	printArr(arr, size);
	bubbleSort(arr, size);
	cout << "After" << endl;
	printArr(arr, size);
}
