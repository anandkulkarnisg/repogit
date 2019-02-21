#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<mutex>
#include<thread>

using namespace std;

std::mutex g_mutex;

void dosomework(const int& id)
{
	std::lock_guard<std::mutex> lock(g_mutex);
	cout << "I am doing some work in thread id = " << id << endl;
}


int main(int argc, char* argv[])
{
	std::vector<std::thread> threads;
	threads.reserve(3);

	for(unsigned int i=0; i<3; ++i)
		threads.push_back(std::thread(dosomework,i));

	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	return(0);
}
