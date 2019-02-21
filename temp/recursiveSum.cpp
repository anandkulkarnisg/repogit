#include<iostream>
#include<string>
#include<vector>

using namespace std;

enum class modeType { even, odd };

// Recursive approach to make one think in terms of sub problems.

// Approach 1.
int sum(const vector<int>& v, const int& idx)
{
	if(idx >= v.size())
		return(0);

	return(v[idx] + sum(v, idx+1));	
}


// Approach 2.
int sum2(const vector<int>& v, const int& idx)
{

	if(idx<0)
		return(0);

	return(v[idx] + sum2(v, idx-1));
}

// Sum only even numbers.
int even_odd_sum(const vector<int>& v, const int& idx,modeType type)
{
	int reminder=1;
	if(type == modeType::even)
		reminder=0;

	if(idx<0)
		return(0);

	if(v[idx]%2 == reminder)
		return(v[idx] + even_odd_sum(v,idx-1,type));
	else
		return(even_odd_sum(v, idx-1,type));	
}

int main(int argc, char* argv[])
{
	vector<int> v = { 1, 2, 3, 4, 5, 6 };
	cout << sum(v,0) << endl;
	cout << sum2(v,v.size()-1) << endl;
	cout << even_odd_sum(v,v.size()-1,modeType::even) << endl;
	cout << even_odd_sum(v,v.size()-1,modeType::odd) << endl;
}
