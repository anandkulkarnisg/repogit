#include<iostream>
#include<string>
#include<thread>
#include<future>
#include<functional>

using namespace std;

int sampleAddFunction(const int& a, const int& b)
{
	int sum = a + b;
	cout << "sum = " << sum << endl;
	return(sum);
}

template<typename T> T asyncExecutor(std::packaged_task<T(T, T)>&& package, const T& dummy1, const T& dummy2)
{
	std::future<T> result = package.get_future();
	std::thread task_td(std::move(package), dummy1, dummy2);
	task_td.join();
	return(result.get());
}

int main(int argc, char* argv[])
{

	// Executing via directly calling through main.
	int testResult1 = sampleAddFunction(100, 200);
	cout << "testResult1 = " << testResult1 << endl;	

	// Attempt to create a std::packaged_task and then run it in another thread.
	std::packaged_task<int(int,int)> task(std::bind(sampleAddFunction, 10, 20));
	std::future<int> result = task.get_future();
	std::thread t(std::move(task), 100, 200); // 100 and 200 are dummy parameters.
	t.join(); 
	int testResult2=result.get();
	cout << "testResult2 = " << testResult2 << endl;

	// Attempt to run this in seperate thread and get results.
	std::packaged_task<int(int,int)> task2(std::bind(sampleAddFunction, 15, 27));
	int testResult3 = asyncExecutor<int>(std::move(task2), 100, 200);
	cout << "testResult3 = " << testResult3 << endl;

}
