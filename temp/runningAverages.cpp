#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

void getRunningAverages(const int arr[], const size_t& size, vector<float>& runningAvg)
{
  float runningAverage=0.0;
  for(unsigned int i=0; i<size;++i)
  {
    int itemSize=i+1;
    runningAverage=(runningAverage*(itemSize-1) + (float)(arr[i]))/(float)(itemSize);
    runningAvg.emplace_back(runningAverage);    
  }  
}

int main(int argc, char* argv[])
{
  int arr[] = {1, 2, 5, 6, 10, 4, 3 };
  const size_t size = sizeof(arr)/sizeof(arr[0]);
  vector<float> runningAvg;
  runningAvg.reserve(size);
  getRunningAverages(arr, size, runningAvg);
  for(const auto& item : runningAvg)
    cout << item << ", ";
  cout << '\n';
  return(0);
}

