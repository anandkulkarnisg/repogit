#include<iostream>
#include<string>

using namespace std;

char intToChar(const int& input)
{
	return(static_cast<char>(input));
}

int main(int argc, char* argv[])
{
	std::string toPrint;
	for(unsigned int i=97; i<97+26; ++i)
	{
		toPrint+=string(1,intToChar(i));
		cout << toPrint << endl;
	}

	toPrint.clear();

    for(unsigned int i=65; i<65+26; ++i)
    {
        toPrint+=string(1,intToChar(i));
        cout << toPrint << endl;
    }

	return(0);
}
