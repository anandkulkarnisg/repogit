#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

bool isPalindrome(const string& inputString)
{
  if(inputString.empty())
    return(false);
  
  stack<char> charStack;
  size_t size = inputString.length();
  
  for(unsigned long i=0; i<size/2; ++i)
    charStack.push(inputString[i]);
  
  int isOdd = size%2;
  
  for(unsigned long i=size/2+isOdd; i<size; ++i)
  {
    if(inputString[i]!=charStack.top())
      return(false);
    charStack.pop();    
  } 
  return(true);
}

bool isPalindromeAlt(const string& inputString)
{
  if(inputString.empty())
    return(false);

  const size_t size = inputString.length();
  int isOdd = size%2;
  
  for(unsigned long i=0; i<size/2-isOdd; ++i)
  {
    if(inputString[i]!=inputString[size-i-1])
      return(false);
  }
  return(true);  
}

int main(int argc, char* argv[])
{
  vector<string> testCaseStrings = { "abcdedcba", "anand", "peter", "abracacarba", "pep", "magicgam", "abcdcba" };
  for(const auto& stringItem : testCaseStrings)
    cout << stringItem << ", " << isPalindrome(stringItem) << endl;
  cout << "-------------------------------------" << endl;
  for(const auto& stringItem : testCaseStrings)
    cout << stringItem << ", " << isPalindromeAlt(stringItem) << endl;
  return(0);
}
