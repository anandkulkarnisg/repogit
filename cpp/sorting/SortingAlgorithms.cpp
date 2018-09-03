
#include<iostream>
#include<string>
#include<cstddef>
#include<SortingAlgorithms.h>

using namespace std;

template<typename T> SortingAlgorithms<T>::SortingAlgorithms(T* argPtr, std::size_t argSize, SortingMode argMode)
{
	ptr = argPtr;
	size = argSize;
	mode = argMode;
}

template<typename T> void SortingAlgorithms<T>::printArray()
{
	T* iterator = ptr;
	for (std::size_t iter = 0; iter <= size - 2; ++iter)
	{
		cout << *iterator << " , ";
		iterator++;
	}
	cout << *iterator << endl;
}

template<typename T> inline bool SortingAlgorithms<T>::sortCondition(T arg1, T arg2)
{

	if (mode == SortingMode::ascending)
		return (arg1 >= arg2);
	else
		return (arg1 <= arg2);
}

template<typename T> void SortingAlgorithms<T>::setSortingMode(SortingMode argMode)
{
	mode = argMode;
}

template<typename T> void SortingAlgorithms<T>::swapItems(T* item1, T* item2)
{
	T temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}

template<typename T> void SortingAlgorithms<T>::runInsertionSort()
{

	T key, j;
	for (std::size_t iterator = 1; iterator < size; ++iterator)
	{
		key = ptr[iterator];
		j = iterator - 1;

		while (j >= 0 && sortCondition(ptr[j], key))
		{
			ptr[j + 1] = ptr[j];
			--j;
		}
		ptr[j + 1] = key;
	}
}

template<typename T> void SortingAlgorithms<T>::runBubbleSort()
{

	for (std::size_t iterator1 = 0; iterator1 < size; ++iterator1)
	{
		for (std::size_t iterator2 = 0; iterator2 < size - (iterator1 + 1); ++iterator2)
		{
			if (sortCondition(ptr[iterator2], ptr[iterator2 + 1]))
				swapItems(&ptr[iterator2 + 1], &ptr[iterator2]);
		}
	}
}

template<typename T> void SortingAlgorithms<T>::runSelectionSort()
{

	for (std::size_t iterator = 0; iterator < size - 1; ++iterator)
	{
		std::size_t min = iterator;
		for (std::size_t iterator2 = (iterator + 1); iterator2 <= size - 1; ++iterator2)
		{
			if (!sortCondition(ptr[iterator2], ptr[min]))
			{
				min = iterator2;
			}
		}
		if (min != iterator)
			swapItems(&ptr[min], &ptr[iterator]);
	}

}

template<typename T> void SortingAlgorithms<T>::runShellSort()
{

	int i, j, k;
	int intSize = static_cast<int>(size);	// We need int interator positions and division with size_t does not end well :(

	for (i = intSize / 2; i > 0; i /= 2)
	{
		for (j = i; j < intSize; ++j)
		{
			for (k = j - i; k >= 0; k -= i)
			{
				if (sortCondition(ptr[k + i], ptr[k]))
					break;
				else
					swapItems(&ptr[k], &ptr[k + i]);
			}
		}
	}
}

template<typename T> long SortingAlgorithms<T>::partition(long low, long high)
{
	long pivot = ptr[high];
	long i = low - 1;
	for (long j = low; j <= high - 1; ++j)
	{
		if (!sortCondition(ptr[j], pivot))
		{
			i++;
			swapItems(&ptr[j], &ptr[i]);
		}
	}
	swapItems(&ptr[i + 1], &ptr[high]);
	return (i + 1);
}

template<typename T> void SortingAlgorithms<T>::quickSort(long low, long high)
{
	if (low < high)
	{
		long partitionIdx = partition(low, high);
		quickSort(0, partitionIdx - 1);
		quickSort(partitionIdx + 1, high);
	}
}

template<typename T> void SortingAlgorithms<T>::runQuickSort()
{
	quickSort(0, static_cast<long>(size - 1));
}

template<typename T> void SortingAlgorithms<T>::heapify(long n, long i)
{
	long largest = i;  // Initialize largest as root
	long l = 2 * i + 1;  // left = 2*i + 1
	long r = 2 * i + 2;  // right = 2*i + 2

	// If left child is larger than root
	if (l < n && sortCondition(ptr[l], ptr[largest])) // switch the comparison to convert the heap structure to either max/min here. This changes the direction of sorting.
		largest = l;

	// If right child is larger than largest so far
	if (r < n && sortCondition(ptr[r], ptr[largest])) // switch the comparison to convert the heap structure to either max/min here. This changes the direction of sorting.
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swapItems(&ptr[i], &ptr[largest]);

		// Recursively heapify the affected sub-tree
		heapify(n, largest);
	}
}

// main function to do heap sort
template<typename T> void SortingAlgorithms<T>::runHeapSort()
{
	long n = static_cast<long>(size);

	// Build heap (rearrange array)
	for (long i = n / 2 - 1; i >= 0; i--)
		heapify(n, i);

	//cout << "In the middle" << endl;
	//printArr(arr, n);
	// One by one extract an element from heap
	for (long i = n - 1; i >= 0; i--)
	{
		// Move current root to end
		swapItems(&ptr[0], &ptr[i]);

		// call max heapify on the reduced heap
		heapify(i, 0);
	}

}

template<typename T> void SortingAlgorithms<T>::merge(long l, long m, long r)
{
	long i, j, k;
	long n1 = m - l + 1;
	long n2 = r - m;

	/* create temp arrays */
	T L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = ptr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = ptr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (!sortCondition(L[i], R[j]))			// switch the comparison direction here to sort the arr in other way.
		{
			ptr[k] = L[i];
			i++;
		} else
		{
			ptr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	 are any */
	while (i < n1)
	{
		ptr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	 are any */
	while (j < n2)
	{
		ptr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
template<typename T> void SortingAlgorithms<T>::mergeSort(long l, long r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		long m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(l, m);
		mergeSort(m + 1, r);
		merge(l, m, r);
	}
}

template<typename T> void SortingAlgorithms<T>::runMergeSort()
{
	mergeSort(0, static_cast<long>(size - 1));
}
