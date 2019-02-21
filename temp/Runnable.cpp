#include<iostream>
#include<string>
#include<thread>
#include<memory>

using namespace std;

template<typename T> class Runnable
{
	private:
		std::thread t;
		void runImpl()
		{
			static_cast<T*>(this)->run();
		}

	public:
		virtual void run() = 0;
		void start()
		{
			t = std::move(std::thread(&Runnable::runImpl, this));
			//t.join(); // without this join there will be a race for the object of this class after item.start() ends and goes out of scope then the very call still to run becomes 
			//indeterminate/undefined behaviour.
		}

		~Runnable()
		{
			std::cout << "I am in the destructor of the base class" << std::endl;
			if(t.joinable())
			{
				std::cout << "joinable" << std::endl;
				t.join();
			}
			else		
				std::cout << "not joinable" << std::endl;
		}
};

class HelloWorld : public Runnable<HelloWorld>
{
	public:
		void run()
		{
			std::cout <<  "I am in thread id = " << std::this_thread::get_id()  << " and the message is : HelloWorld How are you" << std::endl;
		}
};

int main(int argc, char* argv[])
{
	std::cout <<  "I am in the main thread id = " << std::this_thread::get_id()  << std::endl;
	HelloWorld item;
	item.start();
}
