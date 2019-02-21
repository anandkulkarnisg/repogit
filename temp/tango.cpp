#include<iostream>
#include<string>
#include<thread>

using namespace std;

void functionDemo()
{
	std::cout << "I am in this function" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << __func__ << std::endl;
	std::string testFunc = __func__;
	std::cout << "testFunc = " << testFunc.c_str() << std::endl;
}

int main(int argc, char* argv[])
{
	std::thread t(&functionDemo);
	t.join();
	return(0);
}
