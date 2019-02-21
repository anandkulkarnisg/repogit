#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<map>

class TimeUnit_impl
{
	public:
		typedef std::chrono::duration<long, std::ratio<1l, 1000l> > MILLISECONDS;
		typedef std::chrono::duration<long, std::ratio<1l, 1000000l> > MICROSECONDS;
		typedef std::chrono::duration<long, std::ratio<1l, 1l> > SECONDS;
		typedef std::chrono::duration<long, std::ratio<1l, 1000000000l> > NANOSECONDS;
		typedef std::chrono::duration<long, std::ratio<60> > MINUTES;
		typedef std::chrono::duration<long, std::ratio<3600> > HOURS;
};

enum class TimeUnit { MilliSeconds , MicroSeconds , Seconds, NanoSeconds, Minutes, Hours };

void customSleep(const long& quantity, const TimeUnit& unit)
{
	switch(unit)
	{
		case TimeUnit::MilliSeconds : std::this_thread::sleep_for(TimeUnit_impl::MILLISECONDS(quantity));
									  break;
		case TimeUnit::MicroSeconds : std::this_thread::sleep_for(TimeUnit_impl::MICROSECONDS(quantity));
									  break;
		case TimeUnit::Seconds :	  std::this_thread::sleep_for(TimeUnit_impl::SECONDS(quantity));
									  break;
		case TimeUnit::NanoSeconds :  std::this_thread::sleep_for(TimeUnit_impl::NANOSECONDS(quantity));
									  break;
		case TimeUnit::Minutes :	  std::this_thread::sleep_for(TimeUnit_impl::MINUTES(quantity));	
									  break;
		case TimeUnit::Hours :		  std::this_thread::sleep_for(TimeUnit_impl::HOURS(quantity));
									  break;
		default:			std::cout << "error" << std::endl;
							break;
	}
}

std::chrono::milliseconds waitDuration(const long& quantity, const TimeUnit& unit)
{
	// This method converts any given quantity and TimeUnit type to corrosponding millisecond wait period. 
	std::chrono::duration<long, std::ratio<1l, 1000l> > returnValue;
	switch(unit)
	{
		case TimeUnit::MilliSeconds : returnValue = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(quantity));
									  break;
		case TimeUnit::MicroSeconds : returnValue = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::microseconds(quantity));
									  break;
		case TimeUnit::Seconds :	  returnValue = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(quantity));
									  break;
		case TimeUnit::NanoSeconds :  returnValue = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds(quantity));
									  break;
		case TimeUnit::Minutes :	  returnValue = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::minutes(quantity));
									  break;
		case TimeUnit::Hours :		  returnValue = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::hours(quantity));
									  break;
	}

	return(returnValue);
}

using namespace std;

int main(int argc, char* argv[])
{
	// Both possibilities.
	std::this_thread::sleep_for(TimeUnit_impl::SECONDS(5));
	auto now =  std::chrono::high_resolution_clock::now();
	customSleep(10, TimeUnit::Seconds);
	auto then = std::chrono::high_resolution_clock::now();
	std::cout << "Time waited = " << std::chrono::duration_cast<std::chrono::seconds>(then - now).count() << std::endl;
	std::this_thread::sleep_for(waitDuration(10, TimeUnit::MilliSeconds));
	return(0);
}

