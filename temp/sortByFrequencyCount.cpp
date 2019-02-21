#include<iostream>
#include<set>
#include<string>
#include<unordered_map>
#include<utility>

using namespace std;

unordered_map<int, size_t> getFrequencyMap(const int arr[], const size_t& size)
{
  unordered_map<int, size_t> frequencyMap;
  for(unsigned long i=0; i<size; ++i)
  {
    const auto& iter = frequencyMap.find(arr[i]);
    if(iter==frequencyMap.end())
       frequencyMap[arr[i]]=1;
    else
      frequencyMap[arr[i]]=iter->second+1;
  }
  return(frequencyMap);  
}

void sortFrequencyMap(const unordered_map<int, size_t>& frequencyMap)
{
    auto comparatorFunc = [&](const pair<int, size_t>& a, const pair<int, size_t>& b) 
                        { 
                          if(b.second>a.second) return(false); 
                          if(b.second<a.second) return(true);  
      
                          if(b.first>a.first) return(true);
                          if(b.first<a.first) return(false);
      
                          return(false);
                        };
  set<pair<int, size_t>, decltype(comparatorFunc)> sortedSet(comparatorFunc);  
   
 for(const auto& item : frequencyMap)
   sortedSet.insert(make_pair(item.first, item.second));    
  
 for(const auto& setItem : sortedSet)
   cout << setItem.first << ", " << setItem.second << endl;
}

int main(int argc, char* argv[])
{
  int arr[] = { 13, 1, 2, 10, 11, 6, 5, 12, 11, 5, 6, 13, 2 };
  const size_t size = sizeof(arr)/sizeof(arr[0]);
  unordered_map<int, size_t> frequencyMap = getFrequencyMap(arr, size);
  sortFrequencyMap(frequencyMap);
  return(0);
}
