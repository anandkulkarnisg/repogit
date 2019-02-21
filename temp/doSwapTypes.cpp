#include<iostream>
#include<string>

using namespace std;

template<typename T> void doSwap(T& item1, T& item2)
{
 cout << "I am called with references!!" << endl; 
 T temp=move(item1);
 item1=move(item2);
 item2=move(temp);   
}

template<typename T> void doSwap(T* item1, T* item2)
{
  cout << "I am called with pointers!!" << endl; 
  T temp=*item1;
  *item1=*item2;
  *item2=temp;  
}

void testSwaps(int arr[], const size_t& size)
{
  cout << arr[0] << ", " << arr[size-1] << endl;
  doSwap<int>(&arr[0], &arr[size-1]);
  doSwap<int>(arr[0], arr[size-1]);
  cout << arr[0] << ", " << arr[size-1] << endl;  
}

int main(int argc, char* argv[])
{
  int arr[] = { 2, 7, 5 };
  size_t size = sizeof(arr)/sizeof(arr[0]);
  testSwaps(arr, size);
  return(0);
}
