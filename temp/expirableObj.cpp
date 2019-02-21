#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<memory>

using namespace std;

typedef chrono::time_point<chrono::_V2::system_clock, chrono::duration<long, ratio<1l, 1000000000l> > > timePoint;

// class that implements expirable logic.
class expiry
{
	private:
		timePoint m_time;
		long m_expirySecs;

	public:
		expiry(const timePoint& point, const long& secs) : m_time(point), m_expirySecs(secs) { }
		bool isExpired()
		{
			auto now = chrono::high_resolution_clock::now();
			if(chrono::duration_cast<chrono::seconds>(now-m_time).count()>=m_expirySecs)
				return(true);
			else
				return(false);
		}
};

// TestClass inherits expirable Logic.
class TestClass : public expiry
{
	private:
		int m_a = 12;
	public:
		TestClass(const int& input, const long& expiryInSecs) : m_a(input), expiry(chrono::high_resolution_clock::now(), expiryInSecs) { }
		int get()
		{ 
			if(isExpired())
				throw string("The object is expired!");
			return m_a; 
		}
};

// This class is not an expirable class type.
class AnotherClass
{


};

// show an item value.
void showval(TestClass& testClassItem)
{
   try
    {
        int result = testClassItem.get();
		cout << "value is = " << result << endl;
    }
    catch(const string& e)
    {
        cout << e << endl;
    }
}

// Test if a class type is expirable.
template<typename T> bool isExpirable(const T& a)
{
    bool isDerived = false;
    shared_ptr<T> d(new T(a));
    try
    {
        throw d.get();
    }
    catch(expiry* b)
    {
        isDerived = true;
    }
    catch(...)
    {

    }

    return(isDerived);
};


int main(int argc, char* argv[])
{
	TestClass testObj(120, 10);
	AnotherClass testObj2;
	showval(testObj);
	this_thread::sleep_for(chrono::seconds(9)); // works!! still alive.
	showval(testObj);
	this_thread::sleep_for(chrono::seconds(1));	// gone for sure now!
	showval(testObj);
	cout << isExpirable<TestClass>(testObj) << endl;
	cout << isExpirable<AnotherClass>(testObj2) << endl;
	return(0);
}

