#include<iostream>
#include<string>

using namespace std;

enum class DaysOfWeek { Monday , Tuesday, Wednesday , Thursday, Friday, Saturday , Sunday };

int main(int argc, char* argv[])
{
	std::cout << DaysOfWeek::Tuesday << std::endl;
}
