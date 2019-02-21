#include<iostream>
#include<string>

using namespace std;

void assign(int* p)
{
	p = new int;
	*p = 10;
}

int main(int argc, char* argv[])
{
	int *q;
	assign(q);
	std::cout << "value = " << *q << std::endl;
	return(0);
}
