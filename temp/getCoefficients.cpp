#include<iostream>
#include<string>

using namespace std;

int getCoefficientCounts(const int& item1, const int& item2, const int& sum)
{
  unsigned int upperBound=sum/item1;
  int leftOver, solutionCount=0;
  
  for(unsigned int i=1; i<=upperBound; ++i)
  {
    leftOver=sum-(item1*i);
    if(leftOver%item2==0 && leftOver>0)
    {
      cout << "[" << i << ", " << leftOver/item2 << "]" << endl;    
      ++solutionCount;
    }
  }
  return(solutionCount);
}

int main(int argc, char* argv[])
{
  int sum=11600;
  int item1=2;
  int item2=3;  
  cout << getCoefficientCounts(item1, item2, sum) << endl;
  return(0);
}
