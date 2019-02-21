#include<iostream>
#include<string>
#include<memory>

using namespace std;

class SampleClass
{
	public:
		SampleClass()  { std::cout << "constructor called for = " << this << std::endl; }
		~SampleClass() { std::cout << "destructor called for = " << this << std::endl; }
};

int main(int argc, char* argv[])
{
	{
	std::cout << "I am in the block" << std::endl;
	std::unique_ptr<SampleClass> m_ptr = make_unique<SampleClass>(SampleClass());
	std::cout << "I am exiting the block" << std::endl;
	}
}

