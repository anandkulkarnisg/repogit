#include <iostream>
#include <utility>
#include <atomic>

struct A { int a = new (noexcept) int(12); };
struct B { int x, y; };
int main()
{
	std::atomic<A> a;
	std::atomic<B> b;
	std::cout << std::boolalpha
		<< "std::atomic<A> is lock free? "
		<< std::atomic_is_lock_free(&a) << '\n'
		<< "std::atomic<B> is lock free? "
		<< std::atomic_is_lock_free(&b) << '\n';
}
