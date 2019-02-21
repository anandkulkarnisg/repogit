#include<iostream>
#include<string>
#include<mutex>
#include<thread>
#include<vector>
#include<algorithm>
#include<condition_variable>

using namespace std;

int testCounter = 5;
std::mutex m_mutex;
const int threadSize = 100;
bool kickStart = false;
std::mutex cout_mutex;
const long waitTime = 4;

void printOut(const std::string& messageStr)
{
	std::lock_guard<std::mutex> lock(cout_mutex);
	std::cout << messageStr << std::endl;
}

int countDown()
{
	int returnResult;
	std::unique_lock<std::mutex> lock(m_mutex);
	if(testCounter >= 1)
	{
		returnResult = testCounter-1;
		--testCounter;
	}
	else
		throw std::string("Exception : the counter will go down to -ve not allowed");
	lock.unlock();
	return(returnResult);
}

int await()
{
	while(!kickStart) { }
	try
	{
		int returnResult = countDown();
		printOut("The thread recieved a value of " + std::to_string(returnResult));
	}
	catch(const std::string& e)
	{
		printOut(e);	
	}

}

int main(int argc, char* argv[])
{
	std::vector<std::thread> v;
	v.reserve(threadSize);

	for(unsigned int i=0; i<threadSize; ++i)
		v.push_back(std::thread(&await));

	std::cout << "Main Thread starting a wait for " << waitTime << "secs before giving go ahead to the barrier await threads" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(waitTime));
	std::cout << "Setting the kickStart to true now!!" << std::endl;
	kickStart=true;

	std::for_each(v.begin(),v.end(),[&](std::thread& t){ t.join(); });
	return(0);
}
