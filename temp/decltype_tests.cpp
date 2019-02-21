#include<iostream>
#include<string>
#include<type_traits>
#include<vector>

using namespace std;

int main(int argc, char* argv[])
{
  int i=10;
  decltype(i) j=12;
  decltype((i)) k=i;  
  decltype(((i))) l=i;
  decltype(std::move(i)) m= std::move(i);
  decltype(&i) n= &i;
  vector<int> m_vec;
  decltype(m_vec)::value_type o=10;
  int item1;
  float item2;
  decltype(item1+item2) result;    
  
  cout << is_same<decltype(i), decltype(j)>::value;
  cout << is_same<int&, decltype(k)>::value;
  cout << is_same<int&, decltype(l)>::value;
  cout << is_same<int&&, decltype(m)>::value;
  cout << is_same<int*, decltype(n)>::value;
  cout << is_same<int, decltype(o)>::value;
  cout << is_same<float, decltype(result)>::value << endl;
  
  return(0);
}
