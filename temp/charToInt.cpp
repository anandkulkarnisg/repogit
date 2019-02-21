#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
	char c='4';
	cout << static_cast<int>(c)-static_cast<int>('0') << endl;
	return(0);
}
