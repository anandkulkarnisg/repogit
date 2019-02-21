#include<iostream>
#include<string>
#include<tuple>

using namespace std;

int main(int argc, char* argv[])
{
	tuple<string, string, int> t("foo", "bar", 7);
	int i = get<int>(t);        // i == 7
	int j = get<2>(t);          // Same as before: j == 7
	string s = get<string>(t);  // Compile-time error due to ambiguity
	return(0);
}
