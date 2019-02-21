#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

void sortFromPreOrderTraversal(const vector<int>& arr)
{
  // The first item in pre order traversal is the root of binary Tree.
  // Using this as pivot seperate items into left and right Array.
  
  int pivotItem = arr[0];
  const size_t size=arr.size();
  
  vector<int> leftArray, rightArray;
  leftArray.reserve(arr.size()/2+1);
  rightArray.reserve(arr.size()/2+1);
  
  for(unsigned int i=1; i<size; ++i)
  {
    if(arr[i]<pivotItem)
      leftArray.emplace_back(arr[i]);
    else
      rightArray.emplace_back(arr[i]);
  }
  
  leftArray.push_back(arr[0]);

  sort(leftArray.begin(), leftArray.end());
  sort(rightArray.begin(), rightArray.end());
  leftArray.reserve(arr.size());
  
  leftArray.insert(end(leftArray), begin(rightArray), end(rightArray));
  
  for(unsigned int i=0; i<leftArray.size()-1; ++i)
    cout << leftArray[i] << ", ";
  cout << leftArray[leftArray.size()-1] << '\n';
}

int main(int argc, char* argv[])
{
  vector<int> arr = { 5, 2, 1, 3, 4, 8, 6, 7, 9, 10 };  
  sortFromPreOrderTraversal(arr);  
  return(0);
}
