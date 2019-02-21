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

float sampleMultiplyThree(const float& f1, const float& f2, const float& f3)
{
	float result=f1 * f2 * f3;
	return(result);
}


template<typename T, typename F, typename... Ts> T asyncExecutor(F&& package, Ts... args)
{
    std::future<T> result = package.get_future();
    std::thread task_td(std::move(package), args...);
    task_td.join();
    return(result.get());
}

int main(int argc, char* argv[])
{

    std::packaged_task<int(int,int)> task1(std::bind(sampleAddFunction, 20, 45));
    int testResult1=asyncExecutor<int>(std::move(task1), 20, 45);
    cout << "testResult1 = " << testResult1 << endl;

	std::packaged_task<float(float, float, float)> task2(std::bind(sampleMultiplyThree, 12.46, 10.12, 9.58));
	float testResult2=asyncExecutor<float>(std::move(task2), 12.46, 10.12, 9.58); 
	cout << "testResult2 = " << testResult2 << endl;

}

