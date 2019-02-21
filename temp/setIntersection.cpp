#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<unordered_map>

using namespace std;

enum class FetchMode { Common , NonCommon };

set<int> getSetIntersection(const vector<set<int>>& setList, const FetchMode& fetchMode)
{
  size_t reqSize=setList.size();
  unordered_map<int, size_t> m_map;  
  set<int> result;
  size_t count=0;
  
  for(const auto& set : setList)
  {
    for(const auto& setItem : set)
    {
      const auto& iter = m_map.find(setItem);
      if(iter == m_map.end())
          m_map[setItem]=1;
      else
      {
        count=iter->second;
        m_map[setItem]=count+1;
      }          
    }
  }
  
  for(const auto& iter : m_map)
  {
    if(fetchMode == FetchMode::Common)
    {
     if(iter.second == reqSize)
        result.insert(iter.first);
    }
    else
    {
      if(iter.second != reqSize)
        result.insert(iter.first);
    }
  }
  return(result);
}

int main(int argc, char* argv[])
{
  set<int> set1 = { 1, 2, 3, 4 };
  set<int> set2 = { 1, 2, 3, 6, 7 };
  set<int> set3 = { 1, 2, 3, 10, 11 };  
  vector<set<int>> setList = { set1, set2, set3 };
  set<int> result=getSetIntersection(setList, FetchMode::Common);
  for(const auto& item : result)
    cout << item << endl;
  return(0);
}
