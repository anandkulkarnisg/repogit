#include <bits/stdc++.h>
#include<vector>
#include<string>

using namespace std;

vector<int> daysinMonth = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool isLeapJulian(const int& n)
{	
	if(n%4 == 0)
		return(true);
	else
		return(false);
}

bool isLeapGregorian(const int& n)
{

	if(n%400==0)
		return(true);

	if(n%4==0 && n%100!=0)
		return(true);

	return(false);
}

std::string my_solution(const int& n, int mode)
{

	int sum=0;
	int i=1;
	int month=0;
	bool isJulian=false, isGregorian=false;

	if(mode == 0)
		isJulian=true;

	if(mode == 1)
		isGregorian=true;

	while(sum<256)
	{
		if( i == 2 && isJulian && isLeapJulian(n))
			sum +=1;
		if( i ==2 && isGregorian && isLeapGregorian(n))
			sum +=1;
		sum += daysinMonth[i];
		i++;
	}			

	int daysLeft=daysinMonth[i-1]-(abs(256-sum));
	month=i-1;
	string result;
	result.clear();
	result += to_string(daysLeft);
	if(month < 10)
		result += ".0" + to_string(month);
	else
		result += "." + to_string(month);	

	result += "." + to_string(n);	
	return(result);	
}


string solve(int year)
{

	string result;
	result.clear();

	if(year <= 1917)
		result=my_solution(year,0);

	if(year >=1919)
		result=my_solution(year,1);

	if(year == 1918)
	{
		daysinMonth[2]=15;
		result=my_solution(year,2);
	}

	return(result);

}

int main() 
{
	int year;
	cin >> year;
	string result = solve(year);
	cout << result << endl;
	return 0;
}

