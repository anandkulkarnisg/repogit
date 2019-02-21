#include<iostream>
#include<string>
#include<stack>
#include<vector>

using namespace std;

// people ask this question in interview but it is worst kind of implementation and perhaps has no praactical 
// usage. It just tests way of thinking but nothing else.

template<typename T> class SampleQueue
{
  private:
    stack<T> m_stack1;
    stack<T> m_stack2;
  
  public:
      void enqueue(const T& item)
      {
        m_stack1.push(item);
      }
  
      T dequeue()
      {
         if(m_stack1.empty())
           throw std::string("stack is empty");
  
        T returnItem;
         while(!m_stack1.empty())
         {
           T item = m_stack1.top();
           m_stack1.pop();
           m_stack2.push(item);
         }
        
        if(!m_stack2.empty())
        {
          returnItem = m_stack2.top();
          m_stack2.pop();
          while(!m_stack2.empty())
          {
            T item = m_stack2.top();
            m_stack2.pop();
            m_stack1.push(item);
          }
        }
        return(returnItem);        
      } 
};

int main(int argc, char* argv[])
{
  SampleQueue<int> queue;
  vector<int> testVec = { 1, 2, 3, 4, 5, 6, 7 ,8 , 9, 10 };

  for(const auto& iter : testVec)
    queue.enqueue(iter);
  
  for(unsigned int i=0; i<testVec.size(); ++i)
    cout << queue.dequeue() << endl;
  
  try
  {
    cout << queue.dequeue() << endl;
  }
  catch(const std::string& e)
  {
    cout << e << endl;
  }

  return(0);
}
