#include<iostream>
#include<string>
#include<vector>
#include<tuple>

using namespace std;

void sortPricesInfo(vector<tuple<int, int, float>>& pricesInfo)
{
  size_t size = pricesInfo.size();
  for(unsigned int i=1; i<size; ++i)
  {
    tuple<int, int, float> pivotItem = pricesInfo[i];
    float pivot = get<2>(pivotItem);    
    int j=i-1;
    
    while(j>=0 && get<2>(pricesInfo[j])<pivot)
    {
      pricesInfo[j+1]=pricesInfo[j];
      --j;      
    }
    pricesInfo[j+1]=pivotItem;    
  }  
}

void runKnapSackOptimizer(vector<int>& prices, vector<int>& quantities, const long& capacity)
{
  vector<tuple<int, int, float>> pricesInfo;
  size_t size = prices.size();
  pricesInfo.reserve(size);
  
  for(unsigned int i=0; i<size; ++i)
    pricesInfo.emplace_back(make_tuple(prices[i], quantities[i], static_cast<float>(prices[i])/static_cast<float>(quantities[i])));    
  sortPricesInfo(pricesInfo);
  
  long filledCapacity=0;
  float totalCost=0;
  int iter=0;
  
  while(filledCapacity<capacity)
  {
    filledCapacity += get<1>(pricesInfo[iter]);
    totalCost += get<0>(pricesInfo[iter]);
    ++iter;        
  }
   
  if(filledCapacity>capacity)
  {
    iter=iter-1;
    float additionalWeight=filledCapacity-capacity;
    float additionalCost=additionalWeight * get<2>(pricesInfo[iter]);
    totalCost-=additionalCost;
    filledCapacity-=additionalWeight;
  }  

  cout << filledCapacity << ", " << totalCost << endl; 
}

int main(int argc, char* argv[])
{
  /*	
  vector<int> prices = { 10, 5, 15, 7, 6, 18, 3 };
  vector<int> quantities = { 2, 3, 5, 7, 1, 4, 1 };    
  constexpr long capacity = 15;
  */
  
  vector<int> prices = { 60, 100, 120 };
  vector<int> quantities = { 10, 20, 30 }; 
  constexpr long capacity = 50;
      
  runKnapSackOptimizer(prices, quantities, capacity);    
  return(0);
}
