#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<memory>
#include<future>

using namespace std;

std::once_flag flag1;

template<class F, class... Args> void enqueue(F&& f, Args&&... args)
{
	using return_type = typename std::result_of<F(Args...)>::type;
	auto task = std::packaged_task<return_type()> (std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	std::future<return_type> fut = task.get_future();
	//std::call_once(flag1, task);
	task();
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
