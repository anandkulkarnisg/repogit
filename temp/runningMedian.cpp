#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

template<typename T> void printArrayToConsole(const vector<T>& arr, const char* phase)
{
  cout << phase << endl;
  size_t size = arr.size();
  for(unsigned int i=0; i<size-1; ++i)
    cout << arr[i] << ", ";
  cout << arr[size-1] << endl;  
}

void printRunningMedian(const vector<int>& arr, vector<double>& results)
{
  size_t size = arr.size();
  for(unsigned int i=0; i<size; ++i)
  {
    if((i+1)%2==1)
    {
      if(i+1==1)
        results.emplace_back(arr[i]);
      else
      {
        int idx=floor(static_cast<double>(i+1)/static_cast<double>(2));
        results.emplace_back(arr[idx]);
      }
    }
    else
    {
      int idx1 = (i+1)/2;
      int idx2 = idx1-1;
      double temp = static_cast<double>(arr[idx1]+arr[idx2])/static_cast<double>(2);      
      results.emplace_back(temp);
    }    
  }
}

int main(int argc, char* argv[])
{
  vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };  
  vector<double> results;
  results.reserve(arr.size());
  printRunningMedian(arr, results);
  printArrayToConsole<double>(results, "result : ");
  return(0);  
}
