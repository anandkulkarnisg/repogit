#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std;

int getPairSumCount(const int arr[], const size_t& size, const int& sum, unordered_set<string>& results)
{
   unordered_map<int, size_t> countMap;
   for(unsigned int i=0; i<size; ++i)
   {
      const auto& iter = countMap.find(arr[i]);
      if(iter==countMap.end())
        countMap[arr[i]]=1;          
     else
       countMap[arr[i]]=iter->second+1;
   }
  
  int resultCount=0;
  int leftOver;
  for(const auto& iter : countMap)
  {
    leftOver=sum-iter.first;
    const auto& i = countMap.find(leftOver);
    if(i!=countMap.end())
    {
        resultCount+=i->second;
        for(unsigned int j=0; j<i->second; ++j)
          results.insert("[" + to_string(iter.first) + ", " + to_string(leftOver) + "]");
        countMap.erase(i);
    }    
  }
  return(resultCount);
}

int main(int argc, char* argv[])
{
  int arr[] = { 13, 1, 2, 5, 6, 1, 10, 1, 2, 1, 3, 5, 4 };
  const size_t size = sizeof(arr)/sizeof(arr[0]);
  unordered_set<string> results;
  int sum  = 5;
  int result = getPairSumCount(arr, size, sum, results);
  cout << "result = " << result << endl;
  if(result)
  {
    for(const auto& item : results)
      cout << item << endl;
  }
  return(0);
}
