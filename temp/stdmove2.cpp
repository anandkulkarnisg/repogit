#include<iostream>
#include<vector>
#include<string>
#include<utility>

using namespace std;

int main(int argc, char* argv[])
{
	std::string str="Anand Apparao Kulkarni";
	if(str.empty())
		cout << "Empty str!!" << endl;
	else
		cout << "Not empty" << endl;
	vector<std::string> vec;
	vec.push_back(std::move(str));
	cout << "After the move str = " << str << endl;
	if(str.empty())
		cout << "Empty str!!" << endl;
	else
		cout << "Not empty" << endl;

}
