/*
 * SortingAlgorithms.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: anand
 */

#include<iostream>
#include<string>
#include <cxxabi.h>
#include<vector>
#include<functional>
#include<SortingAlgorithms.h>

using namespace std;

int main(int argc, char* argv[]) {

	int arr[] = { 5, 2, 3, 1, 4 };
	std::size_t size = sizeof(arr) / sizeof(arr[0]);
	std::array<std::function<void(SortingAlgorithms<int>&)>, 4> ptr = { &SortingAlgorithms<int>::runInsertionSort, &SortingAlgorithms<int>::runBubbleSort,
			&SortingAlgorithms<int>::runSelectionSort, &SortingAlgorithms<int>::runShellSort };
	std::array<std::string, 4> sortingNames = { "insertionsort", "bubblesort", "selectionsort", "shellsort" };
	std::size_t totalsize = ptr.size();
	SortingAlgorithms<int> integerSorter(&arr[0], size, SortingMode::descending);
	for (std::size_t it = 0; it < totalsize; ++it) {
		integerSorter.setSortingMode(SortingMode::descending);
		cout << "running " << sortingNames[it] << " sorting" << endl;
		cout << "before:-" << endl;
		integerSorter.printArray();
		ptr[it](integerSorter);
		cout << "after descending sort:-" << endl;
		integerSorter.printArray();
		integerSorter.setSortingMode(SortingMode::ascending);
		ptr[it](integerSorter);
		cout << "after ascending sort:-" << endl;
		integerSorter.printArray();
		arr[0] = 5; arr[1]=2 ; arr[2]=3; arr[3]=1; arr[4]=4;
	}
	return (0);

}

