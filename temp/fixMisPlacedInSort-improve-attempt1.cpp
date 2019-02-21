#include<iostream>
#include<string>
#include<utility>
#include<tuple>

using namespace std;

enum class SortOrder { asc, desc };

void printArrayToConsole(const int arr[], const char* phase, const size_t& size)
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

pair<long, SortOrder> getMisPlacedItemIndex(int arr[], const size_t& size)
{  
  tuple<size_t, int, int> tupleArr[2];
  for(unsigned int i=0; i<2; ++i)
  {
    get<0>(tupleArr[0])=0;
    get<1>(tupleArr[0])=0;
    
    get<1>(tupleArr[1])=-1;
    get<1>(tupleArr[1])=-1;
    
    get<2>(tupleArr[1])=-1;
    get<2>(tupleArr[1])=-1;    
  }
  
  tuple<size_t, int, int>& upCount=tupleArr[0];
  tuple<size_t, int, int>& downCount=tupleArr[1];
     
  for(unsigned int i=0; i<size-1; ++i)
  {
    if(arr[i+1]-arr[i]>=0)
    { 
      get<0>(upCount)+=1;
      get<1>(upCount)=i;
      get<2>(upCount)=i+1;
      
      if(get<0>(downCount)>1 && get<0>(upCount)==1)
        return(make_pair(get<1>(upCount), SortOrder::asc));      
    }
    else
    {
      get<0>(downCount)+=1;
      get<1>(downCount)=i;
      get<2>(downCount)=i+1;      
      
      if(get<0>(upCount)>1 && get<0>(downCount)==1)
        return(make_pair(get<1>(downCount), SortOrder::desc));      
    }    
  }
  /*
  for(const auto& item : tupleArr)
    cout << get<0>(item) << ", " << get<1>(item) << ", " << get<2>(item) << endl;  
  */
  
  if(get<0>(downCount)==get<0>(upCount))
    return(make_pair(get<2>(upCount), SortOrder::asc));
  
  return(make_pair(-1, SortOrder::asc));
}
  
void customSortImpl(int arr[], const size_t& size)
{
  pair<long, SortOrder> resultPair = getMisPlacedItemIndex(arr, size);    
  long misPlacedIdx = resultPair.first;    
  SortOrder sortOrder = resultPair.second;
  
  cout << "misedPlacedIdx = " << misPlacedIdx << endl;  
  if(sortOrder == SortOrder::asc)
    cout << "ascending" << endl;
  else
    cout << "descending" << endl;
    
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
 //int arr[] = { 4, 1, 2, 3 };
 //int arr[] = { 1, 4, 3, 2 };
 //int arr[] = { 1, 3, 5, 7, 9, 8 };
 int arr[] = { 1, 4, 2 };
 //int arr[] = { 1, 3, 7, 8, 9, 10, 11, 13, 17, 18 };
 //int arr[] = { 13, 7, 8, 6, 5, 4, 3, 2, 1 }; 
 //int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };  
 //int arr[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };  
 //int arr[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };   
 const size_t size = sizeof(arr)/sizeof(arr[0]);
 printArrayToConsole(arr, "before : ", size);
 customSortImpl(arr, size);
 printArrayToConsole(arr, "after : ", size);
 return(0); 
}
