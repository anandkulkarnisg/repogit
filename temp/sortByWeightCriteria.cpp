#include<iostream>
#include<string>
#include<set>

using namespace std;

void printArrayToConsole(const int arr[], const char* phase, const size_t& size)
{
  cout << phase << endl;
  for(unsigned long i=0; i<size-1; ++i)
    cout << arr[i] << ", ";
  cout << arr[size-1] << '\n';    
}

void sortArrayByWeights(int arr[], int weights[], const size_t& size)
{  
  auto comparatorFunc = [&](const pair<int, int>& w1, const pair<int, int>& w2) 
                            { 
                              if(w1.second>w2.second)
                                return(true);
                              else
                              return(false);                            
                            };
  set<pair<int, int>, decltype(comparatorFunc)> orderedItems(comparatorFunc);
  for(unsigned long i=0; i<size; ++i)
    orderedItems.insert(make_pair(arr[i], weights[i]));
   
  size_t iter=0;
  for(const auto& setItem : orderedItems)
  {
    arr[iter]=setItem.first;
    ++iter;
  }
}

int main(int argc, char* argv[])
{
  int arr[] = {10, 8, 11, 5, 4, 7 };
  int weights[] = {1, 2, 5, 6, 4, 3 };
  const size_t size = sizeof(arr)/sizeof(arr[0]);
  printArrayToConsole(arr, "before : ", size);
  sortArrayByWeights(arr, weights, size);
  printArrayToConsole(arr, "after : ", size);
  return(0);
}
