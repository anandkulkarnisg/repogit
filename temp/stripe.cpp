#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<memory>
#include<boost/shared_ptr.hpp>

using namespace std;

class BaseClass {
private:
	int _member1;
	float _member2;

public:
	BaseClass() { cout << "baseclass :: default ctor called" << endl; _member1=12;_member2=17.456; }
        BaseClass(const BaseClass& ref) { cout << "BaseClass :: copy constructor called" << endl; _member1=ref._member1;_member2=ref._member2; }
        BaseClass& operator=(const BaseClass& ref) { cout << "Baseclass :: assignment operator called" << endl; _member1=ref._member1;_member2=ref._member2; return *this; }
	void show() { cout << "_member1 = " << _member1 << "_member2 = " << _member2 << endl; }
	~BaseClass() { cout << "BaseClass::destructor called" << endl; }
};


int main(int argc,char* argv[]) {

/*
BaseClass b1;
BaseClass b2(b1);
BaseClass b3;
b3=b1;
*/

BaseClass* ptr = new BaseClass();
std::shared_ptr<BaseClass> ptr1(new BaseClass);
boost::shared_ptr<BaseClass> ptr2(new BaseClass);


}
