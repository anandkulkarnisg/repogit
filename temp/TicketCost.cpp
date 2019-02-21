#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<tuple>

using namespace std;

constexpr int DAILY_TICKET_PRICE = 2;
constexpr int WEEKLY_TICKET_PRICE = 7;
constexpr int MONTHLY_TICKET_PRICE = 25;

int WEEKLY_COUNT=0;
int DAILY_COUNT=0;


void resetCostCounters()
{
	WEEKLY_COUNT=0;
	DAILY_COUNT=0;
}

int getTotalCost()
{
	return((WEEKLY_COUNT*WEEKLY_TICKET_PRICE)+(DAILY_COUNT*DAILY_TICKET_PRICE));
}

bool isIrreducible(const vector<int>& argvector)
{
	for(const auto& iterator : argvector)
	{
		if(iterator != 1)
			return false;
	}
	return true;
}

void updateWeeklyWeightCounts(const vector<int>& argvector, map<int,int>& resultmap,tuple<int,int,int>& greedyIndex)
{
	resultmap.clear();
	vector<int> weightcounts;
	size_t size = argvector.size();
	weightcounts.reserve(size);
	int counter=1;
	int max_count=1;
	int max_index=0;
	int max_element=0;
	for(int i=0;i<size;++i)
	{
		for(int j=i+1;j<size;++j)
		{
			if(argvector[i]+6>=argvector[j])
			{
				++counter;	
			}
		}
		if(counter > max_count)
		{
			max_count=counter;
			max_index=i;
			max_element=argvector[i];
		}
		weightcounts.push_back(counter);
		counter=1;
	}

	for(int i=0;i<size;++i)
		resultmap[argvector[i]]=weightcounts[i];

	greedyIndex=std::make_tuple(max_element,max_index,max_count);
}

void showWeeklyWeightCounts(const map<int,int>& resultmap,tuple<int,int,int>& greedyIndex)
{
	cout << " ----------------------------------- " << endl;
	for(const auto& ref : resultmap)
		cout << "Key = " << ref.first << ", Value = " << ref.second << endl;
	cout << "Greedy Index details are " << " Item is = " << std::get<0>(greedyIndex) << " and it is at Index = " << std::get<1>(greedyIndex) << " With a weight = " << std::get<2>(greedyIndex) << endl;
}

void doWeeklyGreedyMerge(vector<int>& argvector, tuple<int,int,int>& greedyIndex)
{

	int greedyItem = std::get<0>(greedyIndex);
	int greedyIdx = std::get<1>(greedyIndex);
	int greedyWeight=std::get<2>(greedyIndex);

	int startIdx=greedyIdx;
	int endIdx=startIdx+greedyWeight;

	/*
	   cout << "I am attempting this erase from " << startIdx << " To " << endIdx << endl;
	   */

	if(greedyWeight == argvector.size() && greedyWeight==1)
	{
		argvector.erase(argvector.begin(), argvector.end());
		++DAILY_COUNT;
		greedyWeight=0;
	}

	if(greedyWeight>3)
	{
		argvector.erase(argvector.begin()+startIdx,argvector.begin()+endIdx);
		++WEEKLY_COUNT;
	}

	if(greedyWeight>1 && greedyWeight<=3)
	{
		argvector.erase(argvector.begin()+startIdx,argvector.begin()+endIdx);
		DAILY_COUNT+=greedyWeight;
	}

	/*
	   cout << "The vector is = " << endl;
	   for(const auto& ref : argvector)
	   cout << "Item = " << ref << endl;
	   */

}

vector<int> getWeeklyWeights(const map<int,int> weeklyWeightCounts)
{

	vector<int> weeklyWeightArray;
	for(const auto& ref : weeklyWeightCounts)
		weeklyWeightArray.push_back(ref.second);
	return(weeklyWeightArray);
}

int solution(vector<int> inputArray)
{
	if(inputArray.size()==0)
		return(0);
	map<int,int> weeklyWeightCounts;
	tuple<int,int,int> greedyIndex;
	vector<int> weeklyWeightArray = {1,2};
	while(!isIrreducible(weeklyWeightArray))
	{
		updateWeeklyWeightCounts(inputArray, weeklyWeightCounts, greedyIndex);
		weeklyWeightArray=getWeeklyWeights(weeklyWeightCounts);
		//showWeeklyWeightCounts(weeklyWeightCounts,greedyIndex);
		doWeeklyGreedyMerge(inputArray,greedyIndex);
	}
	//showWeeklyWeightCounts(weeklyWeightCounts,greedyIndex);
	DAILY_COUNT+=inputArray.size();
	//cout << "WEEKLY COUNT = " << WEEKLY_COUNT << " AND DAILY COUNT = " << DAILY_COUNT << endl;
	int totalCost = getTotalCost();
	if(totalCost > MONTHLY_TICKET_PRICE)
		totalCost=MONTHLY_TICKET_PRICE;
	resetCostCounters();
	return(totalCost);
}

int main(int argc, char* argv[])
{

	vector<int> v1 = { 1,9,10,11,12,23,27,28 };
	vector<int> v2 = { 1,2,4,5,7,29,30 };
	vector<int> v3 = { 1,2,3,10,11,12,13,23,24,25,26,30 };
	vector<int> v4 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,29,30 };
	vector<int> v5 = { 1,15,30 };
	vector<int> v6 = { };
	vector<int> v7 = {1,2,3,4,5,6,7,8,9,10,20,25,30};
	vector<int> v8 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
	vector<int> v9 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
	vector<int> v10 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,26,29,30 };
	vector<int> v11 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,26,29 };
	vector<int> v12 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,29 };
	vector<int> v13 = { 1,5,10,15,20,25,30 };
	vector<vector<int>> testCases;
	testCases.push_back(v1);
	testCases.push_back(v2);
	testCases.push_back(v3);
	testCases.push_back(v4);
	testCases.push_back(v5);
	testCases.push_back(v6);
	testCases.push_back(v7);
	testCases.push_back(v8);
	testCases.push_back(v9);
	testCases.push_back(v10);
	testCases.push_back(v11);
	testCases.push_back(v12);
	testCases.push_back(v13);
	for(auto& inputArray : testCases)
	{
		cout << "Array is = { ";
		for(auto& ref : inputArray)
			cout << ref << " , ";			
		cout << " } , TotalCost = " << solution(inputArray) << endl;
	}
}
