#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

pair<long, float> runKnapSackOptimizer(const vector<int>& prices, const vector<int>& quantities, const long& capacity)
{
 auto comparatorFunc = [&](const pair<int, int>& a, const pair<int, int>& b)
                        {
                          float item1 = static_cast<float>(a.first)/static_cast<float>(a.second);
                          float item2 = static_cast<float>(b.first)/static_cast<float>(b.second);
						  
                          if(item1>item2)
                            return(true);
                          else
                          return(false);
                        };
  
  set<pair<int, int>, decltype(comparatorFunc)> sortedSet(comparatorFunc);
  size_t size=prices.size();
  
  for(unsigned int i=0; i<size; ++i)
    sortedSet.insert(make_pair(prices[i], quantities[i]));
  
  long filledCapacity=0;
  float totalCost=0;
  float lastPricePerQuantity;

  for(const auto& item : sortedSet)
    {
      if(filledCapacity<capacity)
      {
        filledCapacity += item.second;      
        totalCost += item.first;
        lastPricePerQuantity=static_cast<float>(item.first)/static_cast<float>(item.second);
      }
     else
       break;
    }    
  
  if(filledCapacity>capacity)
  {
    float additionalWeight=filledCapacity-capacity;
    float additionalCost=additionalWeight * lastPricePerQuantity;
    totalCost-=additionalCost;
    filledCapacity-=additionalWeight;
  }

  return(make_pair(filledCapacity, totalCost));  
}

int main(int argc, char* argv[])
{
  vector<int> prices = { 60, 100, 120 };
  vector<int> quantities = { 10, 20, 30 }; 
  constexpr long capacity = 50;
  pair<long, float> resultPair=runKnapSackOptimizer(prices, quantities, capacity);
  cout << resultPair.first << ", " << resultPair.second << endl;
  return(0);
}

