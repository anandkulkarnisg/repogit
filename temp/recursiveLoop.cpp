#include<iostream>
#include<vector>
#include<string>

using namespace std;


void printItem(int item, int Limit)
{
	if(item<=Limit)
	{
		cout << item << " " << endl;
		printItem(item+1, Limit);
	}
}

void printItem2(int item, int Limit)
{
	while(item <= Limit)
	{
		cout << item << " " << endl;
		item++;
	}
}

int main(int argc, char* argv[])
{
	 printItem(0, 10);     // recursive loop implementation.
	 printItem2(0, 10);    // Loop using while.
}
