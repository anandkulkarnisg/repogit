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
enum SortingMode {
	ascending, descending
};

template<typename T> class SortingAlgorithms {
private:
	T* ptr;
	std::size_t size;
	SortingMode mode;
	void swapItems(T*, T*);
	bool sortCondition(T, T);

public:
	SortingAlgorithms(T*, std::size_t, SortingMode);
	void printArray();
	void runInsertionSort();
	void runBubbleSort();
	void runSelectionSort();
	void setSortingMode(SortingMode);
};

template<typename T> SortingAlgorithms<T>::SortingAlgorithms(T* argPtr, std::size_t argSize, SortingMode argMode) {
	ptr = argPtr;
	size = argSize;
	mode = argMode;
}

template<typename T> void SortingAlgorithms<T>::printArray() {
	T* iterator = ptr;
	for (std::size_t iter = 0; iter <= size - 2; ++iter) {
		cout << *iterator << " , ";
		iterator++;
	}
	cout << *iterator << endl;
}

template<typename T> inline bool SortingAlgorithms<T>::sortCondition(T arg1, T arg2) {

	if (mode == SortingMode::ascending)
		return (arg1 > arg2);

	if (mode == SortingMode::descending)
		return (arg1 < arg2);
	else
		return (SortingMode::ascending);

}

template<typename T> void SortingAlgorithms<T>::setSortingMode(SortingMode argMode) {
	mode = argMode;
}

template<typename T> void SortingAlgorithms<T>::swapItems(T* item1, T* item2) {
	T temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}

template<typename T> void SortingAlgorithms<T>::runInsertionSort() {

	T key, j;
	for (std::size_t iterator = 1; iterator < size; ++iterator) {
		key = ptr[iterator];
		j = iterator - 1;

		while (j >= 0 && sortCondition(ptr[j], key)) {
			ptr[j + 1] = ptr[j];
			--j;
		}
		ptr[j + 1] = key;
	}
}

template<typename T> void SortingAlgorithms<T>::runBubbleSort() {

	for (std::size_t iterator1 = 0; iterator1 < size; ++iterator1) {
		for (std::size_t iterator2 = 0; iterator2 < size - (iterator1 + 1); ++iterator2) {
			if (sortCondition(ptr[iterator2], ptr[iterator2 + 1]))
				swapItems(&ptr[iterator2 + 1], &ptr[iterator2]);
		}
	}
}

template<typename T> void SortingAlgorithms<T>::runSelectionSort() {

	for (std::size_t iterator = 0; iterator < size - 1; ++iterator) {
		std::size_t min = iterator;
		for (std::size_t iterator2 = (iterator + 1); iterator2 <= size - 1; ++iterator2) {
			if (sortCondition(ptr[iterator2], ptr[min])) {
				min = iterator2;
			}
		}
		if (min != iterator)
			swapItems(&ptr[min], &ptr[iterator]);
	}

}

#endif /* SORTINGALGORITHMS_H_ */
