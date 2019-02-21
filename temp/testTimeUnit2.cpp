#include<iostream>
#include<string>
#include<chrono>
#include<mutex>
#include<thread>
#include<condition_variable>

using namespace std;

enum class TimeUnit { MilliSeconds , MicroSeconds, NanoSeconds };

enum class Fruits { apple = 1, banana, orange , guava };

namespace TimeUtils
{
	template<long T1, long T2> auto toDuration(const long& quantity) -> decltype(std::chrono::duration<long, std::ratio<T1, T2>>(quantity))
	{
		return(std::chrono::duration<long, std::ratio<T1, T2>>(quantity));
	}

	template<TimeUnit> auto getDuration(const long& quantity)
	{
		return(toDuration<1l,1000l>(quantity));
	}

	template<> auto getDuration<TimeUnit::MilliSeconds>(const long& quantity)
	{
		return(toDuration<1l, 1000l>(quantity));	
	}

	template<> auto getDuration<TimeUnit::MicroSeconds>(const long& quantity)
	{
		return(toDuration<1l, 1000000l>(quantity));
	}

	template<> auto getDuration<TimeUnit::NanoSeconds>(const long& quantity)
	{
		return(toDuration<1l, 1000000000l>(quantity));
	}
};

constexpr long mapper(const TimeUnit& unit)
{
	if(unit == TimeUnit::MilliSeconds)
		return(1000l);
}

int main(int argc, char* argv[])
{
	auto wait_millisecs = TimeUtils::getDuration<TimeUnit::MilliSeconds>(100);
	auto wait_microsecs = TimeUtils::getDuration<TimeUnit::MicroSeconds>(100);
	auto wait_generic = TimeUtils::toDuration<1l,mapper(TimeUnit::MilliSeconds)>(100);
	auto wait_hours = TimeUtils::toDuration<60,1l>(100);

	std::this_thread::sleep_for(wait_millisecs);

	auto timeUnitType = TimeUnit::MilliSeconds;
	const long waitPeriod = 100;
	auto wait = TimeUtils::toDuration<1l,mapper(timeUnitType)>(waitPeriod);

	// Had to resort to else if ladder , switch does not work for derivation using auto type specifier.
	// Surprisingly waitTime cant be used / recongnized later.

	/*

	TimeUnit unit = TimeUnit::NanoSeconds;
	const long quantity = 100;
	
	if(unit == TimeUnit::MicroSeconds)
		auto waitTime = TimeUtils::getDuration<TimeUnit::MicroSeconds>(quantity);
	else if(unit == TimeUnit::MilliSeconds)
		auto waitTime = TimeUtils::getDuration<TimeUnit::MilliSeconds>(quantity);
	else if(unit == TimeUnit::NanoSeconds)
		auto waitTime = TimeUtils::getDuration<TimeUnit::NanoSeconds>(quantity);
	else
		auto waitTime = TimeUtils::getDuration<TimeUnit::MilliSeconds>(quantity);	

	std::mutex m_mutex;
	std::condition_variable m_cond;
	std::unique_lock<std::mutex> exclusiveLock(m_mutex);
	m_cond.wait_for(exclusiveLock, wait_millisecs, []() { return(true); });	

	*/
}
