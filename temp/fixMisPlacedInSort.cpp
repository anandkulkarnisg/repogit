#include<iostream>
#include<string>
#include<utility>
#include<vector>

using namespace std;

enum class SortOrder { asc, desc };

void printArrayToConsole(const vector<int>& arr, const char* phase, const size_t& size)
{
  cout << phase << endl;
  for(unsigned long i=0; i<size-1;++i)
    cout << arr[i] << ", ";
  cout << arr[size-1] << '\n';
}

bool sortCompare(const int& item1, const int& item2, const SortOrder& sortOrder)
{
  if(sortOrder==SortOrder::asc)
    return(item1>item2);
  else
    return(item1<item2);
}

pair<long, SortOrder> getMisPlacedItemIndex(vector<int>& arr, const size_t& size)
{
  long result = -1;
  int upCount=0;
  int downCount=0;
  
  for(unsigned int i=0; i<size-1; ++i)
  {
   if(arr[i+1]-arr[i]>=0)
    {
      ++upCount;  
      if(downCount>0 && upCount==1)
        return(make_pair(i+1, SortOrder::desc));
    }
    else
    {
     ++downCount;
     if(upCount>0 && downCount==1)
        return(make_pair(i+1, SortOrder::asc));
    }
  }
  if(upCount>0)
    return(make_pair(result,SortOrder::asc));
  else
    return(make_pair(result,SortOrder::desc));
}
  
void customSortImpl(vector<int>& arr, const size_t& size)
{
  pair<long, SortOrder> resultPair = getMisPlacedItemIndex(arr, size);  
  long misPlacedIdx = resultPair.first;
  SortOrder sortOrder = resultPair.second;
  
  if(misPlacedIdx==-1 || misPlacedIdx>static_cast<long>(size-1))
    return;

  int pivot = arr[misPlacedIdx];
  int j=misPlacedIdx-1;
  
  while(j>=0 && sortCompare(arr[j], pivot, sortOrder))
  {
    arr[j+1]=arr[j];
    --j;
  }
  arr[j+1]=pivot;  
}

int main(int argc, char* argv[])
{ 
 //vector<int> arr = { 4, 1, 2, 3 };   // fails!!
 vector<int> arr = { 1, 3, 2, 5, 7, 9, 11 };  //works!!
 //vector<int> arr = { 1, 3, 5, 7, 9, 8 }; // works!!
 //vector<int> arr = { 2, 2, 2, 2, 2, 2 }; // works!!
  
 //vector<int> arr = { 1, 4, 3, 2 } ; / fails!
 //vector<int> arr = { 11, 9, 7, 5, 6, 3, 2, 1 }; // works!!
 //vector<int> arr = { 11, 9, 7, 5, 3, 1, 2 }; // works!!  
 //vector<int> arr = { 1, 4, 2 }; // works!
  
 const size_t size = arr.size();
 printArrayToConsole(arr, "before : ", size);
 customSortImpl(arr, size);
 printArrayToConsole(arr, "after : ", size);
 return(0); 
}

