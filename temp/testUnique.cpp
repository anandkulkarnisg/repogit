#include<iostream>
#include<string>
#include<memory>

using namespace std;

unique_ptr<int> mPtr_g = make_unique<int>(12);

int main(int argc, char* argv[])
{
	/*
	unique_ptr<int> mPtr = make_unique<int>(12);
	std::cout << "HelloWorld through this message!!" << std::endl;
	*/

    int* rPtr = new int(12);
    unique_ptr<int*> mPtr_k = make_unique<int*>(rPtr);
	rPtr.release();
	delete rPtr;

    /*
	int* rPtr = new int(12);
	unique_ptr<int*> mPtr_k = make_unique<int*>(rPtr);
	mPtr_k.reset();
	delete rPtr;
    */

	return(0);
}
