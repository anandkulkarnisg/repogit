#include<iostream>
#include<string>
#include<memory>

using namespace std;

void testbyReference(const unique_ptr<int>& ref)
{
	std::cout << "ref = " << *ref.get() << std::endl;
}

int main(int argc, char* argv[])
{
	std::unique_ptr<int> mPtr = make_unique<int>(12);	
	testbyReference(mPtr);
	return(0);
}

