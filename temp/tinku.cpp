#include<iostream>
#include<string>
#include<memory>

using namespace std;

int main(int argc, char* argv[])
{
	int* testItem = new int[3];	
	std::shared_ptr<int> testPtr(&testItem[0]);	
	cout << *testPtr.get() << endl;
	return(0);
}
