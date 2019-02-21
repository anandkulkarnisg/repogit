#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

pair<int, int> getMostFrequentItem(const int arr[], const size_t& size)
{
  unordered_map<int, size_t> m_map;
  for(unsigned int i=0; i<size; ++i)
  {
    const auto& iter = m_map.find(arr[i]);
    if(iter == m_map.end())
      m_map.insert(pair(arr[i], 1));
    else
    {
      int count = iter->second;
      m_map[arr[i]]=count+1;  
    }                       
  }
  
  int frequentElement;
  int nextFrequentElement;
  size_t freqElemCount=0;
  size_t nextFreqElemCount=0;
  
  for(const auto& item : m_map)
  {
    if(freqElemCount < item.second)
    {
       nextFrequentElement=frequentElement;
       frequentElement=item.first;
       nextFreqElemCount=freqElemCount;
       freqElemCount = item.second;             
    }    
  }
  cout << freqElemCount << ", " << nextFreqElemCount << endl;
  return(make_pair(frequentElement,nextFrequentElement));
}

int main(int argc, char* argv[])
{
  int arr[] = { 13, 2, 13, 13, 2, 1, 4, 5 };
  const size_t size = sizeof(arr)/sizeof(arr[0]);
  pair<int,int> result = getMostFrequentItem(arr, size);
  cout << result.first << ", " << result.second << endl;
  return(0);
}
