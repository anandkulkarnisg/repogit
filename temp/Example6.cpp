#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<vector>
#include<shared_mutex>

#include "Exchanger.h"

using namespace std;

Exchanger<std::string> exchanger;
std::mutex cout_mutex;
std::mutex m_mutex;
std::condition_variable m_cond;
std::atomic<bool> proceedStatus;
bool finishStatus = false;

void printOut(const std::string& str1, const std::string& str2, const std::thread::id& id)
{
	std::unique_lock<std::mutex> lock(cout_mutex);
	std::cout << str1 << id << str2 << std::endl;
	lock.unlock();
}

void producerThread(const vector<std::string>& refVec)
{
	for(unsigned int i=0; i<refVec.size();++i)
	{
		std::string exchangeString = refVec[i];
		proceedStatus.store(true);
		m_cond.notify_one();
		exchanger.exchange(exchangeString);
		exchanger.reset();
	}
}

void consumerThread()
{
	while(finishStatus != true)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond.wait(lock, [](){ return(proceedStatus == true);});
		lock.unlock();
		std::string returnString = exchanger.exchange("");
		printOut("I am the consumer thread with thread id = ", "I got the message = " + returnString, std::this_thread::get_id());
		proceedStatus=false;
	}
}

int main(int argc, char* argv[])
{
	// Initialize the vector and reserve some space.
	vector<std::string> testVec;
	testVec.reserve(10000);

	// Populate the vector for processing.
	for(unsigned int i=0; i<10000;++i)
		testVec.emplace_back("Test String " + std::to_string(i));	

	// Initialize the proceedStatus to false to begin with.
	proceedStatus.store(false);

	// Create producer and consumer threads , Kick them off.
	std::thread t1(&producerThread, std::cref(testVec));
	std::thread t2(&consumerThread);

	t1.join();
	t2.join();

	return(0);
}

