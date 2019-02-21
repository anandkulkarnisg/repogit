#include <ostream>
#include <fstream>
#include <iostream>

using namespace std;

//https://stackoverflow.com/questions/21064584/ofstream-can-i-redirect-a-cout-into-file

void Display(const std::string& message, std::ostream& os = std::cout)
{
    os << message << std::endl;
	if (os.rdbuf() == std::cout.rdbuf())
	{
		os << "Yes this is cout " << endl;	
	}
}

int main()
{
   const std::string name = "someFile.txt";
   std::ofstream example(name);
   Display("sample message",example);
   //Display("sample message");
   example.close();
}
