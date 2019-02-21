#include<iostream>
#include<vector>
#include<string>
#include<memory>

using namespace std;

int main(int argc, char* argv[])
{

	std::weak_ptr<int> weak_ptr;
	{
		std::shared_ptr<int> ptr(new int(12));
		weak_ptr=ptr;
		if(!weak_ptr.expired())
			cout << "Not yet the Object is alive" << endl;
	}		

	if(weak_ptr.expired())
		cout << "Yes the object is expired now" << endl;

	return(0);
}

