#include<iostream>

using namespace std;

int main(int argc,char *argv[]) 
{

	int rowcount=atoi(argv[1]);
	int jump=abs(atoi(argv[2]));

	for(auto i=1;i<=rowcount;i+=jump) 
	{

		std::string hash(i,'#');
		cout << hash << endl;	
	}

	for(auto i=rowcount;i>=1;i-=jump) 
	{
		std::string hash(i,'#');
		cout << hash << endl;
	}

}
