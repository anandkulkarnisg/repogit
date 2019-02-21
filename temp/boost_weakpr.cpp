#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <thread>
#include <functional>
#include <iostream>

void reset(boost::shared_ptr<int> &sh)
{
	std::cout << "I am attempting to start the reset" << std::endl;
	sh.reset();
	std::cout << "I am done resetting the pointer" << std::endl;
}

void print(boost::weak_ptr<int> &w)
{
	boost::shared_ptr<int> sh = w.lock();
	if (sh)
	{
		std::cout << "I am about to display" << std::endl;
		std::cout << *sh << '\n';
	    std::cout << *sh.get() << '\n';
		std::cout << "I am done displaying the item" << std::endl;
	}
	else
	{
		std::cout << "value has expired!" << '\n';
	}
}

int main(int argc, char* argv[])
{
	boost::shared_ptr<int> sh{new int{99}};
	boost::weak_ptr<int> w{sh};
	std::thread t1{reset, std::ref(sh)};
	std::thread t2{print, std::ref(w)};
	t1.join();
	t2.join();
}
