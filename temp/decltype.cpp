#include<iostream>
#include<vector>
#include<typeinfo>

using namespace std;

template<typename T1, typename T2> auto add(const T1& a, const T2& b) ->decltype(a+b)
{
	return(a+b);
}

int main(int argc, char* argv[])
{
	vector<int> vec;
	decltype(vec)::value_type i = 12;
	cout << i << endl;
	if(typeid(i) == typeid(int))
		cout << "Yes an integer!!" << endl;
	auto result = add(12, "anand");
	cout << result << endl;
	cout << typeid(result).name() << endl;
	return(0);
}
