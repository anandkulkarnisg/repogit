#include<iostream>
#include<string>
#include<thread>
#include<algorithm>
#include<future>
#include<typeinfo>
#include <cxxabi.h>

using namespace std;

template<typename T> std::future<typename std::result_of<T()>::type> spawn_task(T t)
{
	typedef typename std::result_of<T()>::type result_type;
	std::packaged_task<result_type()> task(std::move(t));
	std::future<result_type> res(task.get_future());
	std::thread(std::move(task));
	return res;
}


template<typename T> T spawn_task_variant(T t)
{
	typedef typename std::result_of<T()>::type result_type;
	std::packaged_task<result_type()> task(std::move(t));
	std::future<result_type> res(task.get_future());
	std::thread(std::move(task));
	T result = res.get();
	return(result);
}


template<typename T> T spawn_task_variant_two(std::_Bind<T (*(T, T))(T const&, T const&)> t)
{
	std::packaged_task<T()> task(std::move(t));
	std::future<T> res(task.get_future());
	std::thread thr(std::move(task));
	thr.join();	
	T result = res.get();
	return(result);
}

int func1()
{
	return(20);
}


int func2(const int& a, const int& b)
{
	return(a+b);
}

float func3(const float& f1, const float& f2)
{
	return(f1+f2);
}

template<typename T> T add(const T& t1, const T& t2)
{
	return(t1+t2);
}


int main(int argc, char* argv[])
{

	auto f1=std::bind(func1);
	cout << f1() << endl;

	auto f2=std::bind(func2, 10, 20);
	cout << f2() << endl; 

	auto f3=std::bind(func3, static_cast<float>(11.45), static_cast<float>(25.67)); 
	cout << f3() << endl;

	auto result=spawn_task_variant_two<int>(f2);
	cout << result << endl;

	auto result2=spawn_task_variant_two<float>(f3);
	cout << result2 << endl;

	int result3=add<int>(10, 20);
	cout << result3 << endl;

	auto f4=std::bind(add<int>, 100, 200);
	auto result4=spawn_task_variant_two<int>(f4);
	cout << result4 << endl;

	//int     status;
	//char   *realname;

	//realname = abi::__cxa_demangle(typeid(add<int>).name(), 0, 0, &status);
	//std::cout << typeid(f2).name() << endl;
	//std::cout << "actual type = " << realname << endl;

}
