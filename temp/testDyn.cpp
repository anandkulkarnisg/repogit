#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<map>

using namespace std;

map<string, string> m_map;

void getRecursiveSum(int currSum, int n, int S[], int m, const string& currStr)
{
	if(currSum==n)
	{
		string str = currStr;
		sort(str.begin(), str.end());	
		if(m_map.find(str) == m_map.end())
			m_map[str]=currStr;
		return;
	}

	if(currSum>n)
		return;

	for(unsigned int i=0; i<m; ++i)
	{
		string str = currStr + "+" + to_string(S[i]);
		if(currSum+S[i]<=n)
			getRecursiveSum(currSum+S[i], n, S, m, str); 	
	}
}

void dynSolutions(int S[], const int& m, const int& n)
{
	for(unsigned int i=0; i<m; ++i)
		getRecursiveSum(S[i], n, S, m, to_string(S[i]));
}

int main(int argc, char* argv[])
{
	int S[] = { 1, 2, 3 };
	int m = sizeof(S)/sizeof(S[0]);
	int n = 25;
	dynSolutions(S, m, n);
	cout << "required sum = " << n << endl;
	cout << "total possible solutions = " << m_map.size() << endl;
	cout << "solutions are" << endl;
	for(const auto& iter : m_map)
		cout << iter.second << endl;
	return(0);
}
