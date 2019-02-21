#include<iostream>
#include<string>
#include<chrono>

using namespace std;

class TimeUnit
{
	public:
		constexpr static int MilliSeconds = 1000l;
};

namespace TimeUtils
{
	template<long T1, long T2> std::ratio<T1, T2> getRatioType() 
	{
		return(std::ratio<T1,T2>());
	}
};


int main(int argc, char* argv[])
{
	auto ratioType = TimeUtils::getRatioType<1,TimeUnit::MilliSeconds>();
}

