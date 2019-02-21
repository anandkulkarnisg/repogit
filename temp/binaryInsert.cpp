#include<iostream>
#include<string>
#include<vector>

using namespace std;

void printArrayToConsole(const char* phase, const vector<int>& arr)
{
  cout << phase;
  size_t size = arr.size(); 
  if(size)
  {
    for(unsigned int i=0; i<size-1; ++i) 
      cout << arr[i] << ", ";
    cout << arr[size-1] << '\n';
  }  
}

size_t suggestInsertIdx(const vector<int>& arr, const int& insertItem)
{
  size_t size = arr.size(); 
  long low=0;
  long high=size-1;
  long mid;
  while(low<=high)
  {
    mid=(low+high)/2;
    if(arr[mid]>insertItem) 
    {
      high=mid-1;
    }
    if(arr[mid]<insertItem)
    {
      low=mid+1;
    }
    if(arr[mid]==insertItem)
      return(mid+1);
  }
  return(low);
}

int main(int argc, char* argv[])
{
  vector<int> arr = { 1, 2, 3, 4, 5, 7, 8, 9, 11 };
  vector<int> testCaseItems = { -10, -1, 1, 6, 10, 11, 12, 13, 99 };
  printArrayToConsole("before : ", arr);
  for(const auto& insertItem : testCaseItems)
  {
    size_t insertIdx = suggestInsertIdx(arr, insertItem);
    cout << "item = " << insertItem << " must be inserted at insertIdx = " << insertIdx << endl;
  }
  return(0);
}
