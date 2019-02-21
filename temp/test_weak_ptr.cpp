#include<iostream>
#include<string>
#include<memory>
#include<vector>

using namespace std;

int main(int argc, char* argv[])
{
	std::vector<std::weak_ptr<int>> vec;
	auto sp1 = std::make_shared<int>(10);
	auto sp2 = std::make_shared<int>(20);
	auto sp3 = std::make_shared<int>(30);

	vec.push_back(sp1);
	vec.push_back(sp2);
	vec.push_back(sp3);

	/*
	   sp1.reset();
	   sp2.reset();
	   sp3.reset();
	   */

	for(const auto& iter : vec)
	{
		if(iter.expired())
			std::cout << "The underlying item has expired!!" << std::endl;
		else
			std::cout << "The underlying item has not expired!!" << std::endl;
	}

	for(const auto& iter : vec)
	{
		if(!iter.expired())
		{
			auto sp = iter.lock();
			if(!iter.expired())	// double comparison check because the expired() check if race prone. At the point of iter.lock() the shared_ptr observed by weak_ptr may cease to exist [ in multi thread world ].
			{
				if(*sp.get() == *sp1.get())
					std::cout << "Found the item which had to be unsubscribed!!" << std::endl;
			}
		}
	}
}
