#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
   std::string test = "Anand Apparao ";
   test=test.substr(0,test.length()-1);		
   cout << test.find_last_of(' ') << endl; 	
   return(0);			
}
