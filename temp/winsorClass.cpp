#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<cmath>

using namespace std;

enum class SortOrder { asc, desc };
enum class WinsorStyle { strict, relaxed };

void printArrayToConsole(const char* phase, const vector<int> arr)
{
  cout << phase;
  size_t size = arr.size();
  if(size)
  {
    for(unsigned int i=0; i<size-1; ++i)
      cout << arr[i] << ",";
    cout << arr[size-1] << '\n';
  }
}

void doSwapItems(int* item1, int* item2)
{
  int temp=*item1;
  *item1=*item2;
  *item2=temp;
}

bool doCompare(const int& item1, const int& item2, const SortOrder& sortOrder)
{
  if(sortOrder==SortOrder::asc)
    return(item1<item2);
  else
    return(item1>item2);
}

pair<int, int> doPartialSelectionSort(const vector<int>& orig, const float& winsorSize, const WinsorStyle& winsorStyle=WinsorStyle::strict)
{
  vector<int> arr(orig);
  size_t size=arr.size();
  size_t iterations=round(winsorSize*size)+1;
  size_t minIdx;
  vector<int> results;
  results.reserve(2);
  vector<SortOrder> sortTypes = { SortOrder::asc, SortOrder::desc };

  for(const auto& sortOrder : sortTypes)
  { 
    for(unsigned int i=0; i<iterations; ++i)
    {
      minIdx=i;
      for(unsigned int j=i+1; j<size; ++j)
      {
        if(doCompare(arr[j], arr[minIdx], sortOrder))
          minIdx=j;
      }
      if(minIdx!=i)
        doSwapItems(&arr[i], &arr[minIdx]);
    }    
    size_t resultIdx;    
    float percentileVal;
    resultIdx=iterations-1;
    if(sortOrder == SortOrder::asc)
    {
      //cout << "The index = " << iterations-1 << endl;          
      //cout << "The percentile is = " << static_cast<float>(resultIdx)/static_cast<float>(size-1) << endl;
      percentileVal=static_cast<float>(iterations-1)/static_cast<float>(size-1);
    }
    else
    {
      //cout << "The index = " << (size-1)-(iterations-1) << endl;
      //cout << "The percentile is = " << static_cast<float>(resultIdx)/static_cast<float>(size-1) << endl;
      percentileVal=static_cast<float>((size-1)-(iterations-1))/static_cast<float>(size-1);
    }
    
    if(winsorStyle==WinsorStyle::relaxed)
    {
      if(sortOrder == SortOrder::asc)
      {
        if(percentileVal>winsorSize)
          resultIdx-=1;
      }
      else
      {
        if(percentileVal<(100-winsorSize*100))
          resultIdx-=1;
      }        
    }
    
    results.emplace_back(arr[resultIdx]);
  }
  return(make_pair(results[0], results[1]));
}

void winsorize(vector<int>& arr, const float& winsorSize)
{
  pair<int, int> resultPair=doPartialSelectionSort(arr, winsorSize);
  int lowerBound=resultPair.first;
  int upperBound=resultPair.second;

  size_t size=arr.size();
  for(unsigned int i=0; i<size; ++i)
  {
    if(arr[i]<lowerBound)
      arr[i]=lowerBound;
    else
    {
      if(arr[i]>upperBound)
        arr[i]=upperBound;
    }
  }
}

int main(int argc, char* argv[])
{
  vector<int> arr= { 92, 19, 101, 58, 1053, 91, 26, 78, 10, 13, -40, 101, 86, 85, 15, 89, 89, 28, -5, 41};
  printArrayToConsole("before : ", arr);
  float winsorSize=0.35;
  winsorize(arr, winsorSize);
  printArrayToConsole("after  : ", arr);
  return(0);
}
