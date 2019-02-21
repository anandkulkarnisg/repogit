#include<iostream>
#include<string>
#include<vector>
#include<climits>

using namespace std;

int getMinCoinCombinationsInternal(const vector<int>& coins, const int& sum, bool& isResultSet)
{
	if(sum==0)
		return(0);

	int result=INT_MAX;
	for(unsigned int i=0; i<coins.size(); ++i)
	{
		if(coins[i]<=sum)
		{
			int subResult = getMinCoinCombinationsInternal(coins, sum-coins[i], isResultSet);
			if(subResult != INT_MAX && subResult+1 < result)
			{
				result=subResult+1;
				isResultSet=true;
			}
		}
	}

	return(result);
}

int getMinCoinCombinations(const vector<int>& coins, const int& sum)
{
	bool isResultSet=false;
	int result=getMinCoinCombinationsInternal(coins, sum, isResultSet);
	if(!isResultSet)
		return(0);
	return(result);
} 

int main(int argc, char* argv[])
{
	vector<int> coins = { 9, 6, 5, 1 };
	int sum = 11;
	int result = getMinCoinCombinations(coins, sum);
	cout << result << endl;
	return(0);
}
