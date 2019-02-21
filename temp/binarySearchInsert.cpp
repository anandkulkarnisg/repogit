#include<iostream>
#include<string>
#include<vector>

using namespace std;

long doBinarySearchIdx(const vector<int>& vec, const int& itemToBeInserted)
{
  long low=0;
  long high=vec.size()-1;
  long mid=0;
  long result=-1;
  
  while(low<=high)
  {
    mid=(low+high)/2;
    if(vec[mid]>itemToBeInserted)
      high=mid-1;
    else if(vec[mid]<itemToBeInserted)
      low=mid+1;
    else
	  return(mid);  
}
   
  if(vec[low]<itemToBeInserted)
    return(high);
  
  if(vec[high]>itemToBeInserted)
    return(low);
  
  return(mid);  
}

int main(int argc, char* argv[])
{
 vector<int> vec = { 1, 3, 6, 7, 9, 11, 13, 15, 17, 20, 23, 25 };
 int itemToBeInserted = 11;
 long insertIdx = doBinarySearchIdx(vec, itemToBeInserted);
  
 if(insertIdx == static_cast<long>(vec.size()-1))
   vec.push_back(itemToBeInserted);
 else
    vec.insert(vec.begin()+insertIdx, itemToBeInserted);  
  
 for(unsigned int i=0; i<vec.size()-1;++i)
   cout << vec[i] << ", ";
  cout << vec[vec.size()-1] << '\n';
  return(0);
}

