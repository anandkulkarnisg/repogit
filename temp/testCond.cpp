#include<iostream>
#include<mutex>
#include<condition_variable>

using namespace std;

int main(int argc, char* argv[])
{
	std::mutex m_mutex;
	std::condition_variable m_cond;
	int i = 0;
	std::unique_lock<std::mutex> lock(m_mutex);
	m_cond.wait(lock, [&]() { return(i==0); });
	std::cout << "I am here!!!" << std::endl;
	exit(0);
}
