#include <Poco/Runnable.h>
#include <Poco/Thread.h>
#include <iostream>
#include <memory>

using namespace std;

class MyWorker : public Poco::Runnable
{
public:
  MyWorker() : Runnable() {}

  virtual void run()
  {
	std::cout << "This is a runnable demo" << std::endl;
  }
};

int main()
{
  Poco::Runnable* rptr = new MyWorker();
  std::unique_ptr<Poco::Runnable*> ptr = std::make_unique<Poco::Runnable*>(rptr);
  Poco::Thread t;
  t.start(*(*ptr.get()));
  t.join(); 
  delete rptr;	
  cout << endl << "Threads joined" << endl;

  /*
  Poco::Runnable* ptr = new MyWorker();	
  Poco::Thread t;
  t.start(*ptr);
  t.join();
  delete ptr;
  cout << endl << "Threads joined" << endl;
  */
  return 0;
}
