#include<iostream>
#include<string>
#include<vector>

using namespace std;

int getCombinations(const vector<int>& coins, const int& sum)
{
	vector<int> combinations(sum+1, 0);
	combinations[0]=1;

	for(const auto& coin : coins)
	{
		for(unsigned int i=1; i<combinations.size(); ++i)
		{
			if(i>=coin)
				combinations[i]+=combinations[i-coin];
		}
	}	

	return(combinations[sum]);
}

int main(int argc, char* argv[])
{
	vector<int> coins = { 1, 2, 5 };
	int sum = 12;
	int solution = getCombinations(coins, sum);
	cout << solution << endl;
	return(0);
}
