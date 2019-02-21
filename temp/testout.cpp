#include <fstream>      // std::ofstream
#include <iostream>
#include <string>

using namespace std;

/*
   void Display(const std::string& message, const std::ostream& mycout)
   {
   if(mycout.rdbuf() != std::cout.rdbuf())
   {
   std::ofstream ofs("test.txt", std::ofstream::out);
   ofs << message << endl;
   ofs.close();
   }
   else
   {
   mycout << message << endl;
   }
   }
*/

/*
void display(const std::string& message, const std::ostream& mycout)
{
	mycout << message << endl;
}
*/

void display(const std::string& message, const std::ostream& mycout = std::cout) 
{
    mycout << message << endl;
}

int main() 
{
	display("lorem ipsum", std::cout);
	return 0;
}
