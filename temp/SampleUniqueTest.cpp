#include<iostream>
#include<string>
#include<memory>

using namespace std;

class SampleClass
{
	public:
	SampleClass() { std::cout << "constructor called" << std::endl; }
	~SampleClass() { std::cout << "destructor called" << std::endl; }

};

struct D 
{
    void operator() (SampleClass* p) 
	{
        std::cout << "Calling delete for SampleClass object... \n";
        delete p;
    }
};
 

int main(int argc, char* argv[])
{
	// Lesson : when you use a T* in std::unique_ptr then it will not release the memory and will leak. if T is a trivial type then you have to custom release it else pass a deleter to the unique_ptr.
	// This first piece leaks the integer unless deleted by the explicit delete. 	
	/*
	   std::unique_ptr<int*> m_ptr = make_unique<int*>(new int(12));
	   std::cout << *(*m_ptr.get()) << std::endl;
	   delete *(m_ptr.get());
	   m_ptr.reset();
   */

	// This piece does not leak.
	/*
	std::unique_ptr<int> m_ptr = make_unique<int>(12);
	m_ptr.reset();
	*/	

	// this does not leak as well.
	/*
	std::unique_ptr<SampleClass> m_ptr = make_unique<SampleClass>(SampleClass()); 
	*/

	// This will not leak if a deleter is used.	
	// std::unique_ptr<SampleClass, D> m_ptr(new SampleClass(), D());

	std::unique_ptr<SampleClass> m_ptr1(new SampleClass());		// This is fine.
	std::unique_ptr<SampleClass> m_ptr2 = make_unique<SampleClass>(SampleClass());	// This is fine.
	std::unique_ptr<SampleClass*> m_ptr3 = make_unique<SampleClass*>(new SampleClass());	// This leaks!!
}	
