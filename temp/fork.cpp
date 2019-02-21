#include<iostream>
#include<unistd.h>

using namespace std;

void forkmagic()
{
	fork();
	fork();
	fork();
	cout << "HelloWorld through C++" << endl;
}

int main(int argc, char* argv[])
{
	forkmagic();
	return(0);
}
