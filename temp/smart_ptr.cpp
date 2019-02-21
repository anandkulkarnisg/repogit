#include<iostream>
#include<string>
#include<memory>

using namespace std;

struct B
{
  std::shared_ptr<B> ptr;
};


int main(int argc, char* argv[])
{
	std::shared_ptr<B> x=std::make_shared<B>();
	x->ptr = x; 
	cout << x.use_count() << " , " << x->ptr.use_count() << endl;
	return(0);
}
