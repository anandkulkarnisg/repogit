#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<typename T> class Iterator
{
  private:
    size_t m_size;
    T* m_ptr;
    unsigned long m_currentIdx=0;
  
  public:
    Iterator(vector<T>& input)
    {
      m_size = input.size();
      m_ptr=&input[m_currentIdx];      
    }
    
    bool hasNext()
    {
      if(m_currentIdx>=0 && m_currentIdx<=m_size-1)
        return(true);
      else
        return(false);
    }
    T getNext()
    {
      T retVal = *m_ptr;
      ++m_currentIdx;
      m_ptr++;
      return(retVal);
    }
};

int main(int argc, char* argv[])
{
  vector<int> vec = { 13, 1, 2, 7, 8, 11, 5, 6, 10, 12 };
  Iterator<int> iter(vec);
  
  while(iter.hasNext())
    cout << iter.getNext() << endl;
  
  return(0);  
}
