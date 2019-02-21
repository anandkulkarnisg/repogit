#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

void drawButterFlyToConsole(const string& inputString)
{
  size_t size = inputString.length();
  string subString;
  
  for(unsigned int i=0; i<size; ++i)
  {
    subString=inputString.substr(0, i);        
    if(subString.length())
    {        
        cout << subString << '\n';
    }
  }

  for(int i=size-1; i>=0; --i)
  {
    subString=inputString.substr(0, i);
    if(subString.length())
    {
        cout << subString <<'\n';    
    }
  }
}

int main(int argc, char* argv[])
{
  string sampleString = "Dhruv does drawing!!";
  drawButterFlyToConsole(sampleString);
  return(0);  
}

