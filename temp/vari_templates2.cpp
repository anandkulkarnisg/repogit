#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>

template<class...A, class...B> void func(A...arg1,int sz1, int sz2, B...arg2)  
{
   //assert( sizeof...(arg1) == sz1);
   //assert( sizeof...(arg2) == sz2);
   std::cout << "sizeof parameter pack for A = " << sizeof...(arg1) << std::endl;
   std::cout << "sizeof parameter pack for B = " << sizeof...(arg2) << std::endl;
}

template<typename...A, typename...B> int myfunc(int sz1, int sz2, A...arg1, B...arg2)
{
	assert(sizeof...(arg1) == sizeof...(arg2));
    std::vector<int> p = {(arg1 * arg2)...};
	for(const auto& ref : p)
		std::cout << "vector element = " << ref << std::endl;

    return std::accumulate(p.begin(), p.end(), 0);
}

using namespace std;

int main(void)
{
   //A:(int, int, int), B:(int, int, int, int, int) 
   //func<int,int,int>(1,2,3,3,5,1,2,3,4,5);

   //A: empty, B:(int, int, int, int, int)
   //func(0,5,1,2,3,4,5);
   //return 0;
   
   //func(1,2,3,4,5,6,7,8,9,10);
	
   //func<int,int,int,int>(1,2,3,4,4,4,5,6,7,8);
	
   std::cout << myfunc<int,int,int,int>(4,4,1,2,3,4,5,6,7,8) << std::endl;
}
