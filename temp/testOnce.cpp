#include <iostream>
#include <thread>
#include <mutex>

std::once_flag* flag1 = new std::once_flag;
std::once_flag* flag2 = new std::once_flag;

void simple_do_once()
{
	std::call_once(*flag1, [](){ std::cout << "Simple example: called once\n"; });
}

void may_throw_function(bool do_throw)
{
	if (do_throw) {
		std::cout << "throw: call_once will retry\n"; // this may appear more than once
		throw std::exception();
	}
	std::cout << "Didn't throw, call_once will not attempt again\n"; // guaranteed once
}

void do_once(bool do_throw)
{
	try {
		std::call_once(*flag2, may_throw_function, do_throw);
	}
	catch (...) {
	}
}

int main()
{
	std::thread st1(simple_do_once);
	std::thread st2(simple_do_once);
	std::thread st3(simple_do_once);
	std::thread st4(simple_do_once);
	st1.join();
	st2.join();
	st3.join();
	st4.join();
}
