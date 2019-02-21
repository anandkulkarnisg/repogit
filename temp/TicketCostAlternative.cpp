#include<iostream>
#include<vector>
#include<string>
#include<queue>

using namespace std;

constexpr int DAILY_TICKET_PRICE = 2;
constexpr int WEEKLY_TICKET_PRICE = 7;
constexpr int MONTHLY_TICKET_PRICE = 25;

void buildWeeklyAffinityCounts(const vector<int>& inputVector, queue<int>& affinityCounts)
{

	size_t size=inputVector.size();
	int counter=1;
	for(int i=0;i<size;++i)
	{
		for(int j=i+1;j<size;++j)
		{
			if(inputVector[i]+6>=inputVector[j])
			{
				++counter;      
			}
		}
		affinityCounts.push(counter);
		counter=1;
	}
}

int processWeeklyAffinityCounts(queue<int>& affinityCounts)
{
	if(affinityCounts.empty())
		return(0);
	int DAILY_TICKET_COUNT=0,WEEKLY_TICKET_COUNT=0;
	while(!affinityCounts.empty())
	{
		int item = affinityCounts.front();
		if(item > 3)
		{
			++WEEKLY_TICKET_COUNT;
			for(int i=0;i<item;++i)
				affinityCounts.pop();
		}
		else
		{
			++DAILY_TICKET_COUNT;
			affinityCounts.pop();
		}
	}

	//cout << "Daily Ticket Count = " << DAILY_TICKET_COUNT << ", Weekly Ticket Count = " << WEEKLY_TICKET_COUNT << endl;
	int total_cost=(DAILY_TICKET_COUNT * DAILY_TICKET_PRICE) + (WEEKLY_TICKET_COUNT * WEEKLY_TICKET_PRICE);
	if(total_cost > MONTHLY_TICKET_PRICE)
		return MONTHLY_TICKET_PRICE;
	else
		return total_cost;
}

void displayResult(const vector<int>& inputVector,const int& result)
{
	cout << "Array = { ";
	for(const auto& ref : inputVector)
		cout << ref << " , ";
	cout << "}" << ", TotalCost = " << result << endl;
}

void runTestCases()
{

	vector<int> v1 = { 1,9,10,11,12,23,27,28 };
	vector<int> v2 = { 1,2,4,5,7,29,30 };
	vector<int> v3 = { 1,2,3,10,11,12,13,23,24,25,26,30 };
	vector<int> v4 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,29,30 };
	vector<int> v5 = { 1,15,30 };
	vector<int> v6 = { };
	vector<int> v7 = { 1,2,3,4,5,6,7,8,9,10,20,25,30 };
	vector<int> v8 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	vector<int> v9 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };
	vector<int> v10 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,26,29,30 };
	vector<int> v11 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,26,29 };
	vector<int> v12 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,29 };
	vector<int> v13 = { 1,5,10,15,20,25,30 };
	vector<int> v14 = { 1,2,3,9,10,11,12,19,24,25,26,27,30 };

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
	testCases.push_back(v14);

	queue<int> weeklyAffinityCounts;	
	queue<int> emptyQueue;

	for(auto& inputArray : testCases)
	{
		swap(weeklyAffinityCounts, emptyQueue);
		buildWeeklyAffinityCounts(inputArray, weeklyAffinityCounts);
		int ticketCost=processWeeklyAffinityCounts(weeklyAffinityCounts);
		displayResult(inputArray, ticketCost);	
	}
}

int main(int argc, char* argv[])
{
	runTestCases();
}
