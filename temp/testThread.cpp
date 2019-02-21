#include<iostream>
#include<string>
#include<thread>
#include<mutex>

using namespace std;

std::mutex g_mutex;

void sampleAddFunc(const int& a, const int& b)
{
	int sum=0;
	sum = a+b;
	std::lock_guard<std::mutex> lock(g_mutex);
	cout << "sum is = " << sum << endl;
}

void sampleMultiplyFunc(const int& a, const int& b)
{
	int result=0;
	result = a*b;
	std::lock_guard<std::mutex> lock(g_mutex);
	cout << "multiplication is = " << result << endl;
}

int main(int argc, char* argv[])
{
	std::thread t1(&sampleAddFunc, 10, 20);
	std::thread t2(&sampleMultiplyFunc, 10, 20);

	t1.join();
	t2.join();

	exit(0);
}
