#include<iostream>
#include<memory>

using namespace std;

int main(int argc, char* argv[])
{
	std::unique_ptr<int> testPtr = std::make_unique<int>(12); // unique ownership.
	int* ptr = testPtr.get();	// Take a backup of the location where datum is located on heap!!
	testPtr.release();	// unique ownership released. datum is still in tact.
	cout << "before = " << ptr << endl;
	*ptr+=1;	// This works!!
	// *(ptr)++; // This will blow up as it increments the location to which pointer can point resulting in memory violation.
	(*ptr)++;  // This works fine!!
	cout << *ptr << endl;
	std::shared_ptr<int> sharedPtr(ptr); // Hook the datum to a shared_ptr which will release it.
	return(0);
}
