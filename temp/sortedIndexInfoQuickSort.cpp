#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<typename T> void doSwap(T* item1, T* item2)
{
  T temp=*item1;
  *item1=*item2;
  *item2=temp;  
}

void printArrayToConsole(const int arr[], const char* phase, const long& size)
{
  cout << phase << endl;
  for(long i=0; i<size-1; ++i)
    cout << arr[i] << ", ";
  cout << arr[size-1] << '\n';  
}

void printArrayToConsole(const vector<int> arr, const char* phase, const long& size)
{
  cout << phase << endl;
  for(long i=0; i<size-1; ++i)
    cout << arr[i] << ", ";
  cout << arr[size-1] << '\n';  
}

long doPartition(int arr[], const long& low, const long& high, vector<int>& arrIdx)
{
  long pivotIdx = low + rand()%(high-low);
  doSwap<int>(&arr[pivotIdx], &arr[high]);
  doSwap<int>(&arrIdx[pivotIdx], &arrIdx[high]);  
  
  int pivot=arr[high]; 
  long j=low-1;
  
  for(long i=low; i<high; ++i)
  {
    if(arr[i]<pivot)     
    {
      ++j; 
      doSwap<int>(&arr[i], &arr[j]);
      doSwap<int>(&arrIdx[i], &arrIdx[j]);
    }
  }
  doSwap<int>(&arr[j+1], &arr[high]);
  doSwap<int>(&arrIdx[j+1], &arrIdx[high]);
  return(j+1);  
}

void doQuickSort(int arr[], const long& low, const long& high, vector<int>& arrIdx)
{
  if(low<high)
  {
    long partitionIdx=doPartition(arr, low, high, arrIdx);
    doQuickSort(arr, low, partitionIdx-1, arrIdx);
    doQuickSort(arr, partitionIdx+1, high, arrIdx);    
  }  
}

int main(int argc, char* argv[])
{
  int arr[] = { 13, 1, 2, 10, 7, 8, 5, 4, 12 };
  size_t size = sizeof(arr)/sizeof(arr[0]);
  vector<int> arrIdx(size, 0);
  printArrayToConsole(arr, "before :", size);
  for(unsigned long i=0; i<size; ++i)
    arrIdx[i]=i;
  doQuickSort(arr, 0, size-1, arrIdx);
  printArrayToConsole(arr, "after : ", size);
  printArrayToConsole(arrIdx, "indices : ", size);
  return(0);  
}
