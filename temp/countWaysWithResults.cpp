#include<iostream>
#include<string>
#include<map>
#include<set>

using namespace std;

void storeResults(const string& inputString, set<string>& resultSet)
{
  resultSet.insert(inputString.substr(1, inputString.length()));  
}

long countDP(const string& carryOver, const string& inputString, set<string>& resultSet)
{       
  if(inputString.empty())
  {
    storeResults(carryOver, resultSet);
    return(1);
  }
  
  if(inputString[0]=='0')    
    return(0);
  
  if(inputString.length()==1)
  {
    storeResults(carryOver+","+inputString, resultSet);
    return(1);
  }
    
  string leftOver=inputString.substr(0, 1);
  long result=countDP(carryOver+","+leftOver, inputString.substr(1, inputString.length()), resultSet);
  leftOver=inputString.substr(0, 2);
  if(stoi(leftOver)<=26)   
    result+=countDP(carryOver+","+leftOver, inputString.substr(2, inputString.length()), resultSet);
  
  return(result);  
}

long countWays(const string& inputString, set<string>& resultSet)
{
  if(inputString.empty())
    return(0);
  
  long result=countDP("", inputString, resultSet);
  return(result);  
}

// To store results memoization has to be done away with as caching sub result count results in longer substrings which arent decoded anymore.
int main(int argc, char* argv[])
{
  string inputString="123454321";
  set<string> resultSet;
  long result=countWays(inputString, resultSet);  
  cout << inputString << ", " << result << endl;      
  for(const auto& iter : resultSet)
    cout << iter << endl;
  return(0);
}

