#include<iostream>
#include<string>

using namespace std;

class Base {
private:
	int m_a1;
	float m_a2;
        
};

class Derived : public Base {
private:
	int m_a3;
	double m_a4;
};

int main(int argc,char* argv[]) {

Base*    b = new Derived();
Derived* d = new Derived();

b = d;
//d = b; // Not allowed there is no Derived portion inside Base.

//Derived* d1 = new Base(); // Not allowed A derived pointer cant point to Base class Object.

}
