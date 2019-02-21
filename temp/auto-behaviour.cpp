#include<iostream>
#include<string>

using namespace std;

auto Correct(int i) 
{
  if (i == 1)
    return i;               // return type deduced as int
  else
    return Correct(i-1)+i;  // ok to call it now
}

auto Wrong(int i) 
{
  if (i != 1)
    return Wrong(i-1)+i;  // g++ error : Too soon to call this. No prior return statement.
  else
    return i;             // return type deduced as int
}

int main(int argc, char* argv[])
{
	std::cout << Correct(10) << std::endl;
	std::cout << Wrong(10) << std::endl;
    return(0);
}
