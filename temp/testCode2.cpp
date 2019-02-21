#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<memory>
#include<future>
#include<functional>

using namespace std;

template<class F, class... Args> void enqueue(F&& f, Args&&... args)
{
	using return_type = typename std::result_of<F(Args...)>::type;
	auto task = std::packaged_task<return_type()> (std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	auto fut = task.get_future();		
	try
	{
		task();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	fut.get();
}

class HelloWorld
{

	public:
		void run() { std::cout << "hello world" << std::endl; }
};

HelloWorld hello;

int main(int argc, char* argv[])
{
	enqueue([](){ std::cout << "Simple example: called once\n"; });
	enqueue(std::bind(&HelloWorld::run,hello));
	return(0);
}
