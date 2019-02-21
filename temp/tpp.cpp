#include <type_traits>
#include <iostream>

template <typename...>
struct supportedTypes 
{
	template <typename X>
		static constexpr bool check() { return false; };
};
template <typename A, typename... R>
struct supportedTypes<A, R...> 
{
	template <typename X>
		static constexpr bool check() 
		{
			return std::is_same<X, A>::value
				|| supportedTypes<R...>::template check<X>(); 
		}
};

int main() 
{
	std::cout << supportedTypes<int,double>::check<int>();
	std::cout << supportedTypes<int,double>::check<void>();
	std::cout << supportedTypes<int,double>::check<float>();
}
