#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
	// Wait until main() sends data
	std::unique_lock<std::mutex> lk(m);
	std::cout << "I am here" << std::endl;

	// Read this article to understand the logic of what cv.wait does!
	// https://stackoverflow.com/questions/36315967/c-thread-can-lock-guard-own-a-mutex-that-owned-by-a-unique-lock
	// Esentially wait implementation guarantees in one single atomic operation a) unlocking the lock over mutex and suspension of the thread.

	cv.wait(lk, []{return ready;});

	// after the wait, we own the lock.
	std::cout << "Worker thread is processing data\n";
	data += " after processing";

	// Send data back to main()
	processed = true;
	std::cout << "Worker thread signals data processing completed\n";

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
	lk.unlock();
	cv.notify_one();
}

int main()
{
	std::thread worker(worker_thread);

	data = "Example data";
	// send data to the worker thread
	{
		std::lock_guard<std::mutex> lk(m);
		ready = true;
		std::cout << "main() signals data ready for processing\n";
	}
	cv.notify_one();

	// wait for the worker
	{
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, []{return processed;});
	}
	std::cout << "Back in main(), data = " << data << '\n';

	worker.join();
}
