#include<iostream>
#include<string>
#include<memory>
#include<thread>

using namespace std;

void ThreadFunc(const bool& type)
{
	if(type)
		std::cout << "HelloWorld through C++ concurrency!!" << std::endl;
	else
		std::cout << "Hmm the thread is not joinable?" << std::endl;
}

int main(int argc, char* argv[])
{
	std::thread t1;
	if(t1.joinable())
		std::cout << "Yes it is joinable!!" << std::endl;
	t1 = std::move(std::thread(&ThreadFunc, t1.joinable()));
	if(t1.joinable())
	{
		std::cout << "The thread is joinable!!" << std::endl;
	}
	t1.join();
	return(0);
}
