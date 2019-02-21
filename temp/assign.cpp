#include<iostream>
#include<string>

using namespace std;

void assign(int* ptr)
{
	ptr=400;
}

int main(int argc, char* argv[])
{
	int* item = new int(120);
	assign(item);
	cout << item << endl;
	cout << *item << endl;
	return(0);
}
