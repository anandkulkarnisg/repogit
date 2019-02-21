#include <boost/any.hpp>
#include <typeinfo>
#include <iostream>

int main()
{
	boost::any a = "3.14f";
	if (!a.empty())
	{
		const std::type_info &ti = a.type();
		std::cout << ti.name() << '\n';
	}
}
