#include <boost/atomic.hpp>
#include <thread>
#include <iostream>

boost::atomic<int> a{0};

void thread()
{
	++a;
}

int main(int argc, char* argv[])
{
	std::thread t1{thread};
	std::thread t2{thread};
	t1.join();
	t2.join();
	std::cout << a << '\n';
}
