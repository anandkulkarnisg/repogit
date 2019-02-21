#include<iostream>
#include<string>
#include<thread>
#include<future>
#include<functional>

using namespace std;

int sampleAddFunction(int a, int b)
{
	int sum = a + b;
	cout << "sum = " << sum << endl;
	return(sum);
}

template<typename R, typename F, typename... Ts> R asyncExecutor(F&& package, Ts... args)
{
	std::future<R> result = package.get_future();
	std::thread task_td(std::move(package), args...);
	task_td.join();
	return(result.get());
}

int main(int argc, char* argv[])
{
	std::packaged_task<int(int,int)> task2(std::bind(sampleAddFunction, 20, 45));
	int testResult3 = asyncExecutor<int>(std::move(task2), 10, 20);
	cout << "testResult3 = " << testResult3 << endl;

}
