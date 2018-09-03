/*
 * SortingAlgorithms.h
 *
 *  Created on: Jul 4, 2017
 *      Author: anand
 */

#ifndef SORTINGALGORITHMS_H_
#define SORTINGALGORITHMS_H_

#include<iostream>
#include<string>
#include<cstddef>

using namespace std;
enum SortingMode
{
	ascending, descending
};

template<typename T> class SortingAlgorithms
{
private:
	T* ptr;
	std::size_t size;
	SortingMode mode;
	void swapItems(T*, T*);
	bool sortCondition(T, T);
	long partition(long, long);
	void quickSort(long, long);
	void heapify(long n, long i);
	void merge(long, long, long);
	void mergeSort(long, long);

public:
	SortingAlgorithms(T*, std::size_t, SortingMode);
	void printArray();
	void runInsertionSort();
	void runBubbleSort();
	void runSelectionSort();
	void runShellSort();
	void runQuickSort();
	void runHeapSort();
	void runMergeSort();
	void setSortingMode(SortingMode);
};


#endif /* SORTINGALGORITHMS_H_ */
