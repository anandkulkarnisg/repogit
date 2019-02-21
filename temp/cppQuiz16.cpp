#include <iostream>

// http://cppquiz.org/quiz/question/124?result=OK&answer=21&did_answer=Answer

using namespace std;

struct A {};
struct B {};

template<typename T = A>
struct X;

template<>
struct X<A> {
   static void f() { cout << 1 << endl; }
};

template<>
struct X<B> {
   static void f() { cout << 2 << endl; }
};

template< template<typename T = B> class C>
void g() {
   C<>::f();
}

int main() {
   g<X>();
}

