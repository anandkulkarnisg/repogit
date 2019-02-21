#include<algorithm>
#include<iostream>
#include<set>
#include<string>
#include<unordered_set>

using namespace std;

// Each insertion costs O(1) , overall complexity O(n)
void getUniqueItemsMethod1(const int arr[], const size_t& size)
{
  unordered_set<int> uniqueSet;
  for(unsigned long i=0; i<size; ++i)
    uniqueSet.insert(arr[i]);
  
  for(const auto& setItem : uniqueSet)
    cout << setItem << ", ";  
  cout << '\n';
}

// Each insertion costs O(log(n)) , overall complexity n * O(log(n))=O(nlog(n)) 
void getUniqueItemsMethod2(const int arr[], const size_t& size)
{
  set<int> uniqueSet;
  for(unsigned long i=0; i<size; ++i)
    uniqueSet.insert(arr[i]);
    
  for(const auto& setItem : uniqueSet)
    cout << setItem << ", ";  
   cout << '\n';
}

// sorting takes n * O(log(n)) 
// overall complexity = nO(log(n)) + O(m) [ with m<n , m being size of unique array ] 
// resulting complexity = O(nlog(n))
void getUniqueItemsMethod3(int arr[], const size_t& size)
{
   sort(arr, arr+size);
   unsigned long j=0;
   size_t newSize=0;
  
   for(unsigned long i=0; i<=size; ++i)
   {
     if(arr[i+1]!=arr[i])
     {
       arr[j]=arr[i];
       ++j;
     }     
   }
  newSize=j-1;
  
  for(unsigned long i=0; i<newSize-1; ++i)
    cout << arr[i] << ", ";
  cout << arr[newSize-1] << '\n';
}

int main(int argc, char* argv[])
{
  int arr[] = { 13, 1, 3, 2, 1, 2, 5, 4, 3, 2, 1 };  
  const size_t size = sizeof(arr)/sizeof(arr[0]);
  
  getUniqueItemsMethod1(arr, size);
  getUniqueItemsMethod2(arr, size);
  getUniqueItemsMethod3(arr, size);
  
  return(0);
}
