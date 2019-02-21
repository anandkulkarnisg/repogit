#include<iostream>
#include<string>

using namespace std;

void sampleTestFunc(const int& i)
{
  if(i==0)
    throw(2);
}

void fooThrowsInt(int a) noexcept(true)
{  
   cout << "can throw ints\n" << endl;  
   if (a == 0)  
      throw 1;  
}  

int main(int argc, char* argv[])
{
  const int i=0;
  try
  {
    sampleTestFunc(i);
  }
  catch(int i)
  {
    cout << "caught exception is = " << i << endl;
  }
  return(0);
}
