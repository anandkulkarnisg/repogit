#include<iostream>
#include<string>
#include<thread>
#include<mutex>

using namespace std;

int m_count = 0;
mutex m_mutex;

void runFunc()
{ 
  //lock_guard<mutex> exclusiveLock(m_mutex);
  ++m_count;
}

void runWrapper(const long& runCount)
{
  for(unsigned int i=0; i<runCount; ++i)
    runFunc();
}

int main(int argc, char* argv[])
{
  thread t1(&runWrapper, 100);
  thread t2(&runWrapper, 200);
  t1.join();
  t2.join();  
  cout << "Total number of times the function runFunc is called = " << m_count << endl;
  return(0);  
}
