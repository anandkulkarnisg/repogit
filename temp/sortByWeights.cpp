#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<set>

using namespace std;

void sortPricesByWeights(vector<int>& prices, vector<int>& weights)
{
  //result is 3, 1, 2, 4 [ if weights are same then keep original order ].
  multimap<int,int> m_map;
  typedef std::multimap<int, int>::iterator mmapIter;
  size_t size = prices.size();
  for(unsigned int i=0; i<size; ++i)
    m_map.insert(std::pair<int, int>(weights[i], prices[i]));
  sort(weights.begin(), weights.end(), less<int>());
  set<int> finishedWeights;
  for(unsigned int i=0; i<size; ++i)
  {        
    if(finishedWeights.find(weights[i])==finishedWeights.end())
    {
        pair<mmapIter, mmapIter> result = m_map.equal_range(weights[i]);
        finishedWeights.insert(weights[i]);
        for (mmapIter it = result.first; it != result.second; it++)
        cout << it->second << endl;
    }
  }
}

int main(int argc, char* argv[])
{
  vector<int> prices =  { 2, 4, 3, 1  };
  vector<int> weights = { 2, 1, 3, 3  };
  sortPricesByWeights(prices, weights);
  return(0);
}
