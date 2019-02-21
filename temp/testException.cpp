#include<iostream>
#include<string>
#include<exception>

using namespace std;

const char* IllegalArgumentException_msg = "Exception : Initialization not allowed with -ve permits in strict mode. Use relaxed mode instead.";

struct IllegalArgumentException : public std::exception
{
	std::string param;
	IllegalArgumentException(const std::string& param1) : param(param1) { }

	const char * what () const throw ()
	{
		std::string exceptionMsg = IllegalArgumentException_msg;
		exceptionMsg +=" : " + param;
		return(exceptionMsg.c_str());
	}
};

int main(int argc, char* argv[])
{
	try
	{
		throw IllegalArgumentException("Anand");
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return(0);
}
