#include<iostream>
#include<string>
#include<memory>

using namespace std;

struct thisLeaks
{
   weak_ptr<thisLeaks> m_ptr;
   int m_val;
   thisLeaks(const int& input)
   {
     m_val=input;
   }
};

int main(int argc, char* argv[])
{
  shared_ptr<thisLeaks> testPtr(new thisLeaks(10));  
  testPtr->m_ptr = testPtr;    
  return(0);
}
