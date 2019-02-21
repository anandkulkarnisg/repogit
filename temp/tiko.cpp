#include<iostream>
#include<string>
#include<functional>

using namespace std;

class StringBinder {
	private:
		std::string& ref;
	public:
		StringBinder(const std::string& copyref) 
		{
			ref = copyref;	
		}
		void show() 
		{
			cout << "String is = " << ref << " at " << this << endl;
		}
};

int main(int argc,char* argv[]) {

	std::string sampleString = "Anand";
	cout << "original string block is at = " << &sampleString << endl;
	StringBinder a(sampleString);
	a.show();
    sampleString = "New val";
    a.show();

}
