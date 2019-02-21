#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

/*template <unsigned int m, unsigned int n> class countWaysT 
  {
  public:
  enum {
  if(n > 1)
  value = countWaysT<m, (m - n)>::value + countWaysT<m,(m-(n-1))>::value
  else
  value = 1
  }; 
  };


  template <unsigned int m, 1> class countWaysT  
  {
  public:
  enum {
  value = 1
  };  
  };*/


// Adding memoization support to the below.

map<long long,long long> memo;
map<long long, long long>::iterator iter;

long long countWays(int totalSteps, bool useMemoization)
{

	if(totalSteps < 0)
		return(0);

	if(totalSteps == 0)
		return(1);

	if( useMemoization)
	{
		iter=memo.find(totalSteps);
		if(iter != memo.end())
		{
			return(iter->second);	
		}
	}

	long long resultSteps=0;
	if(totalSteps > 0)
	{
		resultSteps=countWays(totalSteps-3, useMemoization) + countWays(totalSteps-2, useMemoization) + countWays(totalSteps-1, useMemoization);
		if(useMemoization)
			memo[totalSteps]=resultSteps;
		return(resultSteps);
	}
}

int main(int argc, char* argv[])
{
	// Without memoization : blows up around 37/38 step.
	// with memoization : blows up around 87/88 with long long step.

	unsigned int Limit=50;
	if ( argc >= 2)
	{
		int temp = atoi(argv[1]);
		if( temp < Limit) 			
			Limit= temp;
	}

	vector<int> testCaseList;
	testCaseList.reserve(Limit);
	for(unsigned int i=0; i<Limit; ++i)
		testCaseList.push_back(i);

	for(const auto& testCaseItem : testCaseList)
		cout << "Input = " << testCaseItem << ", the possible ways is = " << countWays(testCaseItem, false) << endl;

}
