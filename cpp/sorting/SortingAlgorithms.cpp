/*
 * SortingAlgorithms.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: anand
 */

#include<iostream>
#include<string>
#include<SortingAlgorithms.h>

using namespace std;

int main(int argc, char* argv[])
{
	int arr[] = { 5, 2, 3, 1, 4 };
	std::size_t size = sizeof(arr)/sizeof(arr[0]);

	// Insertion sort example
	SortingAlgorithms<int> integerSorter(&arr[0], size, SortingMode::descending);
	cout << "before :" << endl;
	integerSorter.printArray();
	integerSorter.runInsertionSort();
	cout << "after :" << endl;
	integerSorter.printArray();
	integerSorter.setSortingMode(SortingMode::ascending);
	integerSorter.runInsertionSort();
	cout << "after :" << endl;
	integerSorter.printArray();

	// Bubble sort example.
	int arr2[] = { 5, 2, 3, 1, 4 };
	size = sizeof(arr2)/sizeof(arr2[0]);
	SortingAlgorithms<int> integerSorter2(&arr2[0], size, SortingMode::descending);
	cout << "before :" << endl;
	integerSorter2.printArray();
	integerSorter2.runBubbleSort();
	cout << "after :" << endl;
	integerSorter2.printArray();
	integerSorter2.setSortingMode(SortingMode::ascending);
	integerSorter2.runBubbleSort();
	cout << "after :" << endl;
	integerSorter2.printArray();

	return(0);
}


