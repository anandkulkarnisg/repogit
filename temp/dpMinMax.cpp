#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

// get the max/min of an array using dp without iterative solution.

// array traversion from right to left.
int getMax(const int arr[], const size_t& size)
{
  if(size==0)
    return(arr[0]);
  
  return(max(arr[size-1], getMax(arr, size-1)));  
}

int getMin(const int arr[], const size_t& size)
{
  if(size==0)
    return(arr[0]);
  
  return(min(arr[size-1], getMin(arr, size-1)));  
}

// array traversion from left to right.
int getMaxAlt(const int arr[], const size_t& size, const size_t& index=0)
{
  if(index==size-1)
    return(arr[index]);
  
  return(max(arr[index], getMaxAlt(arr, size, index+1)));  
}

int getMinAlt(const int arr[], const size_t& size, const size_t& index=0)
{
  if(index==size-1)
    return(arr[index]);
  
  return(min(arr[index], getMinAlt(arr, size, index+1)));  
}

int main(int argc, char* argv[])
{
  int arr[] = { 11, 6, 5, 2, 10, 7, 3, -1 };
  const size_t size = sizeof(arr)/sizeof(arr[0]);
  cout << "-----------------" << endl;
  cout << getMax(arr, size) << endl;
  cout << getMin(arr, size) << endl;
  cout << "-----------------" << endl;
  cout << getMaxAlt(arr, size) << endl;
  cout << getMinAlt(arr, size) << endl;
  cout << "-----------------" << endl;
  return(0);
}

