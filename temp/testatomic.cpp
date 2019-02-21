#include<iostream>
#include<string>
#include<memory>
#include<atomic>

using namespace std;

int main(int argc, char* argv[])
{
	std::shared_ptr<std::atomic<int>> testPtr(new atomic<int>(12));
	std::cout << testPtr.use_count() << std::endl;
	return(0);
}
