#include<iostream>
#include<string>
#include<vector>
#include<cxxabi.h>
#include<typeinfo>

using namespace std;

std::string classname(const std::type_info& info)
{
    int status;
    char* rslt=abi::__cxa_demangle(info.name(),0,0,&status);
    std::string result(rslt);
    free(rslt);
    return result;
}

class TestClass
{
private:
		int m_a;
		int m_b;
		std::vector<int> m_vec;

public:
		TestClass() : m_a(10), m_b(12), m_vec({1,2,3,4}) { }
		TestClass(const TestClass& copyRef) 
		{ 
			std::cout << "copy called" << std::endl; 
			this->m_a = copyRef.m_a; 
			this->m_b = copyRef.m_b; 
			this->m_vec = copyRef.m_vec; 
		}
		TestClass& operator=(const TestClass& assignRef) 
		{ 
			std::cout << "assignment called" << std::endl; 
			this->m_a = assignRef.m_a; 
			this->m_b = assignRef.m_b; 
			this->m_vec = assignRef.m_vec; 
			return(*this); 
		}

		TestClass(TestClass&& movecopyRef) 
		{ 
			std::cout << "move copy called" << std::endl; 
			this->m_a = movecopyRef.m_a;  
			this->m_b = movecopyRef.m_b; 
			this->m_vec = std::move(movecopyRef.m_vec);
			movecopyRef.m_vec = { }; 
		}
		TestClass& operator=(TestClass&& moveassignRef) 
		{ 
			std::cout << "move assignment called" << std::endl;
			this->m_a = moveassignRef.m_a;
			this->m_b = moveassignRef.m_b;
			this->m_vec = std::move(moveassignRef.m_vec); 
			moveassignRef.m_vec = { };
			return(*this);
		}

		void show()
		{
			std::cout << "m_a = " << m_a << " , " << "m_b = " << m_b << ", m_vec(size) = " << m_vec.size() << std::endl;
		}
};


// Old world way of relaying function and their inability to forward arguments as they are passed.

template<typename T> void foo(T arg)
{

	std::cout << "The type of input that came is " << classname(typeid(arg)) << std::endl;
	arg.show(); 
}

template<typename T> void relay(T arg)
{
	foo(arg);
}

template<typename T> void relay_new(T&& arg)
{
	foo(std::forward<T>(arg));
}

int main(int argc, char* argv[])
{
	/*
	TestClass item1;
	TestClass item2(item1);
	TestClass item3;
	item3 = item1;
	TestClass item4 = std::move(TestClass());
	*/

	// Call the old world style relay.
	TestClass item1;
	relay<TestClass>(item1);	// Two copies caused out of this.	

	// Try forwarding temporary objects.
	relay<TestClass>(TestClass());	// One copy called as first copy is perhaps eliminated by compiler optimization and only second copy works from relay -> foo.	

	std::cout << "-------------" << std::endl;

	TestClass& ref = item1;

	// Try the new world now.
	relay_new<TestClass>(std::move(ref));

	relay_new<TestClass>(TestClass());



}
