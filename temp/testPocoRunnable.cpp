#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<chrono>
#include<memory>
#include<Poco/Runnable.h>
#include<Poco/Thread.h>

using namespace std;
using namespace Poco;

class MyWorker : public Runnable
{
	public:
		MyWorker() : Runnable() {}

		virtual void run()
		{
			std::cout << "This is a poco runnable demo. Must be called only once!!" << std::endl;
		}
		~MyWorker() { std::cout << "destructor called" << std::endl; }
};

int main(int argc, char* argv[])
{
	Runnable* item = new MyWorker();
	unique_ptr<Runnable> m_ptr1(item); // This also works!
	unique_ptr<once_flag> m_onceFlag(new once_flag);
	m_onceFlag.reset(new once_flag);
	if(m_onceFlag.get() != nullptr)
		std::cout << "Yup still holding on an active object!" << std::endl;
	m_onceFlag.reset();
	    if(m_onceFlag.get() == nullptr)
        std::cout << "Yup now it is null indeed!" << std::endl;
	return(0);
}

