/*
 * HelloWorld.cpp
 *
 *  Created on: Jun 25, 2017
 *  Author: Anand Kulkarni.
 */

#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>
#include<deque>
#include<condition_variable>

using namespace std;
std::mutex g_mutex;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

bool exitFlag = true;

void concurrentHelloWorld(const int& id) {
	std::lock_guard<std::mutex> lock(g_mutex);
	cout << "HelloWorld though Concurrent C++ via thread id = " << id << endl;
	if (id == 2) {
		while (1 != 2 && exitFlag) {
			cout << "Stuck and fucked up in thread id = " << id << endl;
		}
		cout << "Finally out of the mess!!" << endl;
	}
}

void sampleThreadDemo() {
	std::thread t1(concurrentHelloWorld, 1);
	std::thread t2(concurrentHelloWorld, 2);
	t1.join();
	t2.detach();
}

void producerThread() {

	int count = 10;
	int lowerbound;
	int copyCount = count;
	while (true) {
		lowerbound = count - 10;
		while (count > lowerbound) {
			std::unique_lock<std::mutex> lock(mu);
			cout << "Producer pushing in value = " << count << endl;
			q.push_front(count);
			lock.unlock();
			cond.notify_all();
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			--count;
		}
		count = copyCount + 10;
		copyCount = count;
	}
}

void consumerThread() {

	int data = 0;
	while (true) {
		data = 0;
		while (data != 1) {
			std::unique_lock<std::mutex> locker(mu);
			cond.wait(locker, []() {return !q.empty();});
			data = q.back();
			q.pop_back();
			locker.unlock();
			cout << "consumer got data = " << data << endl;
		}
	}
}

void demoConsumerProducer() {

	std::thread t1(producerThread);
	std::thread t2(consumerThread);
	std::thread t3(consumerThread);
	std::thread t4(consumerThread);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

int main(int argc, char* argv[]) {

	std::vector<int> testVector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	cout << "HelloWorld through C++/Eclipse IDE/Linux/CDT Tools" << endl;
	for (const auto& iter : testVector)
		cout << iter << endl;
	sampleThreadDemo();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	exitFlag = false;
	demoConsumerProducer();
	return (0);
}

