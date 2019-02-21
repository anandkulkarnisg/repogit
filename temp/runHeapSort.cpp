#include<iostream>
#include<string>

using namespace std;

void doSwap(int* item1, int* item2)
{
	int temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}

void printArrayToConsole(const int arr[], const char* phase, const int& size)
{
	cout << phase << endl;
	for(int i=0; i<size-1;++i)
		cout << arr[i] << ",";
	cout << arr[size-1] << '\n';
}

void doHeapify(int arr[], const int& size, const int& i)
{
	int largest=i;
	int leftChildIdx=2*i+1;
	int rightChildIdx=2*i+2;

	if(leftChildIdx <size && arr[leftChildIdx] <= arr[largest])
		largest=leftChildIdx;
	if(rightChildIdx <size && arr[rightChildIdx] <= arr[largest])
		largest=rightChildIdx;
	
	if(largest != i)
	{
		doSwap(&arr[i], &arr[largest]);
		doHeapify(arr, size, largest);
	}
}

void runHeapSort(int arr[], const int& size)
{
	for(int i=(size/2)-1;i>=0;--i)
	{
		doHeapify(arr, size, i); 
	}
	
	for(int i=size-1;i>=0;--i)
	{
		doSwap(&arr[i], &arr[0]);
		doHeapify(arr, i, 0);
	}
}

int main(int argc, char* argv[])
{
  int arr[] = { 10, 11, 13, 9, 2, 5, 8, 4, 6 };
  size_t size = sizeof(arr)/sizeof(arr[0]);
  printArrayToConsole(arr, "before : ", size);
  runHeapSort(arr,size);
  printArrayToConsole(arr, "after : ", size);
  return(0);  
}
