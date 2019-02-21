#include<iostream>
#include<vector>
#include<map>

using namespace std;

map<std::string, int> recursionMap;

int count( vector<int> S, int m, int n )
{

	std::string key, value;
	key = "count(S[], " + to_string(m) + "," + to_string(n) + ")";

	// If n is 0 then there is 1 solution (do not include any coin)
	if (n == 0)
	{
		//recursionMap[key]=1;
		return 1;
	}

	// If n is less than 0 then no solution exists
	if (n < 0)
	{
		//recursionMap[key]=0;
		return 0;
	}

	// If there are no coins and n is greater than 0, then no solution exist
	if (m <=0 && n >= 1)
	{
		//recursionMap[key]=0;
		return 0;
	}

	// count is sum of solutions (i) including S[m-1] (ii) excluding S[m-1]
	int result1 = count(S, m-1, n);
	int result2 = count(S, m, n-S[m-1]);
	return result1 + result2;
}


int main(int argc, char* argv[])
{
	
	for(unsigned int i=1; i<=10; ++i)
	{
		vector<int> S ;
		for(unsigned int j=1; j<=i; ++j)
		{
			S.push_back(j);
		}
		int m = S.size();
		int n = 10;
		cout << i << "," << count(S, m ,n) << endl;
	}

	vector<int> S = { 3, 4 };
	int n = 10;
	cout << count(S,2,n) << endl;		


}
