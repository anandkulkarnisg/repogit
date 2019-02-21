#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
	// allocate a 2d array.
	int **arr = new int*[10];
	for(unsigned int i=0; i<=9; ++i)
		arr[i] = new int[10];

	// complete the code to cleanup the allocation above.
	for(unsigned int i=0; i<=9; ++i)
		delete[] arr[i];
	delete[] arr;
	
	return(0);
}
