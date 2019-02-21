#include<iostream>
#include<string>
#include<set>

using namespace std;

string boolString(const bool& input)
{
  if(input)
    return("true");
  return("false");
}

bool isUnique(const int arr[], const size_t& size)
{
  set<int> m_set;
  for(unsigned int i=0; i<size; ++i)
  {
    const auto& iter = m_set.find(arr[i]);
    if(iter!=m_set.end())
      return(false);
    else
      m_set.insert(arr[i]);    
  }
  return(true);
}

int main(int argc, char* argv[])
{
  int arr[] = { 13, 1, 2, 10, 9, 6, 4 };
  size_t size = sizeof(arr)/sizeof(arr[0]);
  string result = boolString(isUnique(arr, size));
  cout << result << endl;
  return(0);  
}
