#include<iostream>
#include<vector>
#include<string>
#include<queue>

using namespace std;

constexpr int DAILY_TICKET_PRICE = 2;
constexpr int WEEKLY_TICKET_PRICE = 7;
constexpr int MONTHLY_TICKET_PRICE = 25;

constexpr int WEEKLY_RANGE=6;
constexpr int DAILY_COUNT_LIMIT=3;

int GetOptimizedTicketCost(const vector<int>& inputVector)
{

	size_t size = inputVector.size();
	int WEEKLY_TICKET_COUNT=0;
	int DAILY_TICKET_COUNT=0;
	int counter=1;
	for(int i=0;i<size;++i)
	{
		for(int j=i+1;j<size;++j)
		{
			if(inputVector[i] + WEEKLY_RANGE >= inputVector[j])
			{
				++counter;
			}
		}
		if(counter > DAILY_COUNT_LIMIT)
		{
			++WEEKLY_TICKET_COUNT;

			// Algorithm should jump by counter value when doing greedy selection for weekly ticket.
			// but we do it by counter-1 as the differece of 1 is covered by ++i of the outer i loop.

			i+=counter-1; 
		}
		else
		{
			++DAILY_TICKET_COUNT;
		}
		counter=1;
	}

	//cout << "BreakDown is DAILY_TICKET_COUNT = " << DAILY_TICKET_COUNT << " And WEEKLY_TICKET_COUNT = " << WEEKLY_TICKET_COUNT << endl;
	int ticketCost = (DAILY_TICKET_PRICE * DAILY_TICKET_COUNT) + (WEEKLY_TICKET_PRICE * WEEKLY_TICKET_COUNT);
	if(ticketCost > MONTHLY_TICKET_PRICE)
		ticketCost = MONTHLY_TICKET_PRICE;

	return(ticketCost);
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
    testCases.reserve(15);
    testCases = { v1, v2 , v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14 };

	for(auto& testcaseItem : testCases)
	{
		int ticketCost;
		ticketCost=GetOptimizedTicketCost(testcaseItem);
		displayResult(testcaseItem, ticketCost);	
	}
}

int main(int argc, char* argv[])
{
	runTestCases();
}
