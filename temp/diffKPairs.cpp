#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int getDiffKCount(int arr[], const int& size, const int& diff)
{
	std::sort(arr, arr+size);
	int returnCount=0;
	int lowerBound=0;
	int upperBound=0;
	int diffAmt=0;

	while(upperBound<size)
	{
		diffAmt=arr[upperBound]-arr[lowerBound];
		if(diffAmt==diff)
		{
			++returnCount;
			++upperBound;
			++lowerBound;
		}
		else if(diffAmt>diff)		
				++lowerBound;
		else
			++upperBound;
	}	
	return(returnCount);
}

int main(int argc, char* argv[])
{
	int arr[] = {1, 5, 3, 4, 2}; 
	size_t size = sizeof(arr)/sizeof(arr[0]);
	int diffK = 3;
	int solution = getDiffKCount(arr, size, diffK);
	cout << "solution = " << solution << endl;
	return(0);
}
