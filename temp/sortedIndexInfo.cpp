#include<iostream>
#include<string>
#include<vector>

using namespace std;

void printArrayToConsole(const vector<int>& arr, const char* phase, const size_t& size)
{
  cout << phase << endl;
  for(unsigned long i=0; i<size-1; ++i)
    cout << arr[i] << ", ";
  cout << arr[size-1] << '\n';  
}

void doInsertionSort(vector<int>& arr, const size_t& size, vector<int>& vecIdx)
{  
  vector<int> copyArr(arr);
  for(unsigned long i=1; i<size; ++i)
  {
    int pivot=arr[i];
    long j=i-1;
    
    while(j>=0 && arr[j]>pivot)
    {
     arr[j+1]=arr[j];
     vecIdx[j+1]=vecIdx[j]; 
     --j; 
    }
    arr[j+1]=pivot;        
    vecIdx[j+1]=i;
  }
  arr=copyArr;
}

int main(int argc, char* argv[])
{
  vector<int> arr = { 3, 2, 1, 5 };
  vector<int> copyArr = arr;
  size_t size = arr.size();
  vector<int> vecIdx(size, 0);
  for(unsigned long i=0; i<size; ++i)
    vecIdx[i]=i;
  printArrayToConsole(arr, "before :", size);
  doInsertionSort(arr, size, vecIdx);
  printArrayToConsole(arr, "after :", size);
  printArrayToConsole(vecIdx, "indices :", size);
  cout << "result = " << endl;
  for(unsigned long i=0; i<size-1; ++i)
    cout << copyArr[vecIdx[i]] << ", ";
  cout << copyArr[vecIdx[size-1]] << '\n';
  return(0);
}
