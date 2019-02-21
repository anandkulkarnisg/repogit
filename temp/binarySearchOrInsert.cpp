#include<iostream>
#include<string>
#include<vector>

using namespace std;

enum class binarySearchMode { search, insert };

template<typename T> void printArrayToConsole(const char* phase, const vector<T>& arr)
{
  cout << phase << endl;
  size_t size=arr.size();
  if(size)
  {
    for(unsigned long i=0; i<size-1;++i)
      cout << arr[i] << ", ";
    cout << arr[size-1] << '\n'; 
  }  
}

template<typename T> long doBinarySearch(const vector<T>& arr, const T& item, const binarySearchMode& mode=binarySearchMode::search)
{
  size_t size=arr.size();
  long low=0;
  long high=size-1;
  long mid;

  while(low<=high)
  {
    mid=(low+high)/2;
    if(arr[mid]>item)
    {
      high=mid-1;      
    }
    if(arr[mid]<item)
    {
      low=mid+1;      
    }
    if(arr[mid]==item)
    {
      return(mid);
    }    
  }

  if(mode==binarySearchMode::search)
    return(-1);
  else
    return(low);
}

int main(int argc, char* argv[])
{
  vector<int> arr = { 1, 2, 3, 4, 5, 7, 8, 9, 11, 12, 13 };
  printArrayToConsole<int>("before : ", arr);
  vector<int> testCaseItems = { -99, -10, -1, 0, 1, 6, 10, 12, 13, 15, 59, 99 };
  cout << "#########################################" << endl;
  cout << "Insert suggestions from the binarySearch" << endl;
  cout << "#########################################" << endl;
  for(const auto& insertItem : testCaseItems)
  {
    long insertIdx =  doBinarySearch<int>(arr, insertItem,binarySearchMode::insert);
    cout << "The item = " << insertItem << " needs to be inserted at index = " << insertIdx << endl;    
  }  
  cout << "#########################################" << endl;
  cout << "search suggestions from the binarySearch" << endl;  
  cout << "#########################################" << endl;
  for(const auto& searchItem : testCaseItems)
  {
    long searchIdx =  doBinarySearch<int>(arr, searchItem);
    if(searchIdx != -1)
      cout << "The item = " << searchItem << " is found at index = " << searchIdx << endl;        
    else
      cout << "The item = " << searchItem << " is not found in the arr." << endl;
  }  
  return(0);
}

