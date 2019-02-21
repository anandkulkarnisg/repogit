#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main(int, char**)
{
    string text = "token,test,string";
    char_separator<char> sep(",");
    tokenizer<char_separator<char>> tokens(text, sep);
    for (const auto& t : tokens) 
	{
        cout << t << "." << endl;
    }
}
