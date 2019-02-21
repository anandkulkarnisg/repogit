#include <iostream>
#include <memory>

int main()
{
	auto sp = std::make_shared<int>(42);
	auto sp2 = std::make_shared<int>(42);
	std::weak_ptr<int> wk1 = sp;
	std::weak_ptr<int> wk2 = sp;
	const std::weak_ptr<int>& wk3 = sp;
	std::cout << wk3.expired() << std::endl;
	std::cout << wk1.expired() << std::endl;
	
	if(*sp.get() == *sp2.get())		
		std::cout << "comparison works!!" << std::endl;		
	std::cout << "sp.get() = " << sp.get() << std::endl;
	std::cout << "sp2.get() = " << sp2.get() << std::endl;

	auto sp3 = wk3.lock();
	if(*sp3.get() == *sp.get())
		std::cout << "weak ptr upgrade works" << std::endl;
}
