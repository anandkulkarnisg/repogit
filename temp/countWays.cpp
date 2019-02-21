#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

long countDP(const string& inputString, map<string, long>& memo)
{
  if(inputString.empty())
    return(1);

  if(inputString[0]=='0')
    return(0);

  if(inputString.length()==1)
    return(1);

  const auto& iter=memo.find(inputString);
  if(iter!=memo.end())
    return(iter->second);

  long result=countDP(inputString.substr(1, inputString.length()), memo);
  if(stoi(inputString.substr(0, 2))<=26)
    result+=countDP(inputString.substr(2, inputString.length()), memo);

  memo[inputString]=result;
  return(result);  
}

long countWays(const string& inputString)
{
  if(inputString.empty())
    return(0);

  map<string, long> memo;
  long result=countDP(inputString, memo);
  return(result);  
}

int main(int argc, char* argv[])
{
  cout << "string, countWays" << endl;
  for(unsigned long i=0; i<21; ++i)
  {
    string inputString(i, '1');
    long result=countWays(inputString);
    cout << inputString << ", " << result << endl;    
  }  
  return(0);
}
