#include <boost/atomic.hpp>
#include <thread>
#include <iostream>

boost::atomic<int> a{0};
int b = 0;

void thread1()
{
	b = 1;
	a.store(1, boost::memory_order_release);
}

void thread2()
{
	int attempts=0;
	while (a.load(boost::memory_order_acquire) != 1)
	{
		attempts++;
	}
	std::cout << b << '\n';
	std::cout << attempts << std::endl;
}

int main()
{
	std::thread t1{thread1};
	std::thread t2{thread2};
	t1.join();
	t2.join();
}
