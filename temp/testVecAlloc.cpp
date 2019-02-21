#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(int argc, char* argv[])
{
	vector<int> vec;
	vec.reserve(10);
	for(int i=0;i<10;++i)
		vec[i]=i*2;
	for(int i=0;i<10;++i)
		cout << vec[i] << ",";
	cout << endl;
	
	cout << "utterly fails via iterators and size as well" << endl;
	cout << "via iterators" << endl;
	for(const auto& iter : vec)
		cout << iter << endl;
	cout << "size="<<vec.size() << endl;
	
	return(0);	
}
