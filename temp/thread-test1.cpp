#include<iostream>
#include<string>
#include<thread>
#include<memory>
#include<future>

using namespace std;

void JustDoASimpleLoopSum(const int& n,std::promise<int>&& prms)
{
	auto sum = 0;
	for(unsigned int i=1; i<=n; ++i)
		sum += i;
	cout << sum << endl; 
	prms.set_value(sum);
}

int main(int argc, char* argv[])
{
	std::promise<int> prms;
	future<int> fut = prms.get_future();
	std::thread t1(&JustDoASimpleLoopSum, 10, std::move(prms));
	int result = fut.get();
	cout << "result is = " << result << endl;
	t1.join();
	return(0);	
}


